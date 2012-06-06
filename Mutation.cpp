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
#include "llvm/Assembly/Writer.h"

#include <iostream>
#include <fstream>

using namespace llvm;

STATISTIC(MutationCounter, "Counts the number of mutated functions");

namespace {
  struct Mutation : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Mutation() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      errs() << "In function ";
      errs().write_escaped(F.getName());
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
                  std::string ncallee = callee.append("_ov");
                  Value *FPthread = F.getParent()->getOrInsertFunction(ncallee.data(), NFPTy, PAL);
                  
                  // Create the arguments for the new call
                  std::vector<Value*> Args(CS.arg_begin(), CS.arg_end());
                  Value * MutVal = ConstantInt::get (IntegerType::get (F.getContext(),32), MutationCounter);
                  Args.push_back(MutVal);
                  
                  // Add the new call instruction to the basic block
                  CallInst::Create(FPthread,  ArrayRef<Value*>(Args), "", BI);

                  // Remove the original pthread function call
                  I->eraseFromParent();
                  
                  //F.viewCFG(); // View the cfg
//                  Value *VBB = dyn_cast<Value>(&BB);
//                  WriteAsOperand(errs() , VBB, true, F.getParent());
//                  errs() << "\n";
//                    
//                  for (pred_iterator PI = pred_begin(&BB), E = pred_end(&BB); PI != E; ++PI) {
//                    BasicBlock *Pred = *PI;
//                    Value *VPred = dyn_cast<Value>(&*Pred);
//                    
//                    WriteAsOperand(errs() , VPred, true, Pred->getParent()->getParent());
//                    errs() << "\n";
//                  }
//                  
//                  Value *VF = dyn_cast<Value>(&F);
//                  errs() << "# uses = " << VF->getNumUses() << "\n";
//                  errs() << "type = " << VF->getType() << "\n";
//
//                  if(F.hasAddressTaken()){
//                     errs() << "There are indirect uses\n";
//                  }
//                  
//                  for (Value::use_iterator i = F.use_begin(), e = F.use_end(); i != e; ++i){                     
//                     //i->dump();
//                     //i->getType()->dump();
//                     errs() << "\n";
//                     if(Instruction *Inst = dyn_cast<Instruction>(*i)){
//                      errs() << "F is used in instruction:\n";
//                      errs() << *Inst << "\n";
//                     }
//                     if(User *U = dyn_cast<User>(*i)){
//                        if(isa<Constant>(U)){
//                           errs() << "It's a constant\n";
//                        }
//                        if(isa<Instruction>(U)){
//                           errs() << "It's an instruction\n";
//                        }
//                        if(isa<Operator>(U)){
//                           errs() << "It's an operator\n";
//                           Operator *Oper = dyn_cast<Operator>(U);
//                        }
//                        errs() << "User " << U->getNumOperands() << "\n";
//                        Value *BOp = U->getOperand(0);
//                        BOp->dump();
//                        if (isa<Function>(BOp)) {
//                           errs() << "Is a function\n";
//                        }
//                        if(Instruction *Inst = dyn_cast<Instruction>(BOp)){
//                           errs() << "F is used in instruction: " << *Inst << "\n";
//                        }
//                     }                   
//                  }
                  //CallInst *CI = IRB.CreateCall(FPthread, ArrayRef<Value*>(Args));                                
//               }
             }  
          }
       }
      }
      return false;
    }
    
    virtual bool doFinalization(Module &M){
       std::ofstream ofile;
       
       ofile.open ("stats.log");
       ofile << MutationCounter;
       ofile.close();
       
       return true;
    }
/*    
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    }
*/
   bool isPThreadCall(std::string callee){
      const int ptfnum = 3;
      std::string ptfnames[ptfnum] = {"pthread_mutex_lock", "pthread_cond_wait", "pthread_create"};
       
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
