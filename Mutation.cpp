//===- Mutation.cpp - Online Mutation Analysis for LLVM ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "mutation"

#include "llvm/Constants.h"
#include "llvm/Operator.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Value.h"
#include "llvm/Function.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Module.h"
#include "llvm/Attributes.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/CallSite.h"
#include "llvm/Support/CFG.h"
#include "llvm/Analysis/DebugInfo.h"
#include "llvm/Analysis/Trace.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/Assembly/Writer.h"

#include <iostream>
#include <fstream>

using namespace llvm;

STATISTIC(MutationCounter, "Counts the number of mutated functions");

namespace {
  struct Mutation : public FunctionPass {
    std::multimap<std::string, CallInst*> PThreadCreateCallMap;
    
    static char ID; // Pass identification, replacement for typeid
    Mutation() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      typedef SmallPtrSet<const Value*, 16> SmallValueSet;
      SmallValueSet DFSet;
      
      std::string fname = F.getName().str();
      errs() << "In function ";
      errs().write_escaped(fname);
      errs() << " we called:\n";

      for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
         BasicBlock &BB = *FI;
         for (BasicBlock::iterator BI = BB.begin(), BE = BB.end(); BI != BE;) {
            Instruction *I = BI++;
            if (isa<CallInst>(I) || isa<InvokeInst>(I)) {
               // In case of a Call or Invoke get the called function
               CallSite CS = CallSite(I);
               Value *CFV = CS.getCalledValue();
               std::string callee = CFV->getName().str();
             
               if(isPThreadCall(callee)){
                  // In case of a pthread function we mutate
                  errs().write_escaped(callee) << "\n";
                  
                  IRBuilder<> IRB(I);                                
                  ++MutationCounter;

                  // Build a new function with an extra int argument
                  Function *FP = cast<Function>(CFV);
                  // Get the type of function
                  FunctionType *FPTy = FP->getFunctionType();
                  // Create a new array of params with all the old params and an extra int
                  std::vector<Type*> Params(FPTy->param_begin(), FPTy->param_end());
                  Params.push_back(IntegerType::get (F.getContext(),32));
                  ArrayRef<Type*> AParams = ArrayRef<Type*>(Params);
                  
                  // Create the new function type for the overloaded function
                  FunctionType *NFPTy = FunctionType::get(FP->getReturnType(), AParams, FPTy->isVarArg());
                  // Create a new attribute list 
                  AttrListPtr PAL = FP->getAttributes().addAttr(Params.size(), Attributes(Attribute::InReg));                  
                                    
                  // Create a new function and add it to the module
                  std::string scallee = std::string(callee);
                  std::string ncallee = callee.append("_ov");
                  Value *FPthread = F.getParent()->getOrInsertFunction(ncallee.data(), NFPTy, PAL);
                  
                  // Create the arguments for the new call
                  std::vector<Value*> Args(CS.arg_begin(), CS.arg_end());
                  Value * MutVal = ConstantInt::get (IntegerType::get (F.getContext(),32), MutationCounter);
                  Args.push_back(MutVal);
                  
                  // Add the new call instruction to the basic block
                  CallInst *NCI = CallInst::Create(FPthread,  ArrayRef<Value*>(Args), "", BI);
                  
                  // In case of a pthread_create we add to our multimap
                  if(scallee.compare("pthread_create") == 0){
                     errs() << "pthread_create calls ";
                     User *idf = dyn_cast<User>(CS.getArgument(2));
                     Value *ff = idf->getOperand(0);
                     std::string ptcreate_callee = ff->getName().str();
                     errs().write_escaped(ptcreate_callee) << "\n";
                     PThreadCreateCallMap.insert(std::pair<std::string, CallInst*>(ptcreate_callee,NCI));
                  }
                  
                  std::vector<BasicBlock *> Path;
                  std::vector<BasicBlock *> Visited;
                  BasicBlock *ebb = (&(BB.getParent()->getEntryBlock()));
                  Path = findPath(&BB, ebb, Path, Visited);
                  
                  int psize = (int) Path.size();
                  if(psize > 0){
                     errs() << "Found a path to the entry block\n";
                     errs() << "size: " << psize << "\n";
                     for(std::vector<BasicBlock *>::iterator it=Path.begin(); it < Path.end(); it++){
                        BasicBlock *PBB = *it;
                        ppBasicBlock(PBB);
                     }
                  }
                  
                  //F.viewCFG(); // View the cfg

//                  Value *VF = dyn_cast<Value>(&F);
//                  errs() << "# uses = " << VF->getNumUses() << "\n";
//                  errs() << "type = " << VF->getType() << "\n";
//
//                  if(F.hasAddressTaken()){
//                     errs() << "There are indirect uses\n";
//                  }                               

                  // Remove the original pthread function call
                  I->replaceAllUsesWith(NCI);
                  I->eraseFromParent();
               }  
            }
         }
      }
      return false;
    }
    
    virtual bool doInitialization(Module &M){
       return true;
    }
    
    virtual bool doFinalization(Module &M){
       std::ofstream ofile;
       
       ofile.open ("stats.log");
       ofile << MutationCounter;
       ofile.close();
       
       errs() << "Dumping our pthread_create multimap\n";
       for (std::multimap<std::string,CallInst*>::iterator it=PThreadCreateCallMap.begin() ; it != PThreadCreateCallMap.end(); it++ )
          errs() << (*it).first << " => " << (*it).second << "\n";
         
       return true;
    }
/*    
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    }
*/
   std::vector<BasicBlock *> findPath(BasicBlock* bb, BasicBlock* ebb, std::vector<BasicBlock *> Path, std::vector<BasicBlock *>Visited){
      // Control Flow Analysis -- Going back from the current instruction
      // until the first basic block of the function and collect all terminators.
      
      // Insert the current element into both vectors
      Visited.push_back(bb);
      
      std::vector<BasicBlock *>ToVisit;
      
      // Get the entry block for this function
      
      if(bb == ebb){
         Path.push_back(bb);
         return Path;
      }
      
      // We first check all the predecessors to see if the entry block is there
      for (pred_iterator PI = pred_begin(bb), E = pred_end(bb); PI != E; ++PI) {
         BasicBlock *Pred = *PI;         
         // If this element is the entry element we stop
         if(Pred == ebb){
            Path.push_back(Pred);
            Path.push_back(bb);
            return Path;
         }
         ToVisit.push_back(Pred);
      }                       
      
      std::vector<BasicBlock *>::iterator it;
      std::vector<BasicBlock *>::iterator fit;

      for(it=ToVisit.begin(); it < ToVisit.end(); it++){
         BasicBlock *BB = *it;
         
         fit = std::find(Visited.begin(), Visited.end(), BB);

         if(BB == *fit){
            continue;
         }
         
         std::vector<BasicBlock *>NPath = findPath(BB, ebb, Path, Visited);
         int npsize = (int) NPath.size();
         if(npsize > 0){
            NPath.push_back(bb);
            return NPath;
         }
      }
      
      return Path;
    }
    
   void ppBasicBlock(BasicBlock* bb){
      Value *VBB = dyn_cast<Value>(bb);
      WriteAsOperand(errs() , VBB, true, bb->getParent()->getParent());
      errs() << "\n";      
   }

   bool isPThreadCall(std::string callee){
      const int ptfnum = 75;
      std::string ptfnames[ptfnum] = {"pthread_attr_destroy","pthread_attr_getdetachstate","pthread_attr_getguardsize",
      "pthread_attr_getinheritsched","pthread_attr_getschedparam","pthread_attr_getschedpolicy","pthread_attr_getscope",
      "pthread_attr_getstackaddr","pthread_attr_getstacksize","pthread_attr_init","pthread_attr_setdetachstate",
      "pthread_attr_setguardsize","pthread_attr_setinheritsched","pthread_attr_setschedparam","pthread_attr_setschedpolicy",
      "pthread_attr_setscope","pthread_attr_setstackaddr","pthread_attr_setstacksize","pthread_cancel",
      "pthread_cond_broadcast","pthread_cond_destroy","pthread_cond_init","pthread_cond_signal",
      "pthread_cond_timedwait","pthread_cond_wait","pthread_condattr_destroy","pthread_condattr_getpshared","pthread_condattr_init",
      "pthread_condattr_setpshared","pthread_create","pthread_detach","pthread_equal","pthread_exit","pthread_getconcurrency",
      "pthread_getschedparam","pthread_getspecific","pthread_join","pthread_key_create","pthread_key_delete","pthread_mutex_destroy",
      "pthread_mutex_getprioceiling","pthread_mutex_init","pthread_mutex_lock","pthread_mutex_setprioceiling","pthread_mutex_trylock",
      "pthread_mutex_unlock","pthread_mutexattr_destroy","pthread_mutexattr_getprioceiling","pthread_mutexattr_getprotocol",
      "pthread_mutexattr_getpshared","pthread_mutexattr_gettype","pthread_mutexattr_init","pthread_mutexattr_setprioceiling",
      "pthread_mutexattr_setprotocol","pthread_mutexattr_setpshared","pthread_mutexattr_settype","pthread_once","pthread_rwlock_destroy",
      "pthread_rwlock_init","pthread_rwlock_rdlock","pthread_rwlock_tryrdlock","pthread_rwlock_trywrlock","pthread_rwlock_unlock",
      "pthread_rwlock_wrlock","pthread_rwlockattr_destroy","pthread_rwlockattr_getpshared","pthread_rwlockattr_init",
      "pthread_rwlockattr_setpshared","pthread_self","pthread_setcancelstate","pthread_setcanceltype","pthread_setconcurrency",
      "pthread_setschedparam","pthread_setspecific","pthread_testcancel"};
       
      for(int i = 0; i < ptfnum; i++){
         if(callee.compare(ptfnames[i]) == 0){
            return true;
         }
      }
      return false;
   }
  };
}

char Mutation::ID = 0;
static RegisterPass<Mutation> X("mutation", "Mutation for pThreads");
