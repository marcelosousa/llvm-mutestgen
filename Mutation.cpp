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
#include "llvm/Support/CallSite.h"
#include "llvm/Constants.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Value.h"
#include "llvm/Function.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CallSite.h"
#include "llvm/Analysis/DebugInfo.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Attributes.h"

#include <iostream>
#include <fstream>

using namespace llvm;

STATISTIC(PthreadCallsCounter, "Counts number of pthread functions called");

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Mutation : public FunctionPass {
    Value * FPthread;
    static char ID; // Pass identification, replacement for typeid
    Mutation() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      unsigned dbgKind = F.getContext().getMDKindID("dbg");
      std::string filename = "<unknown>";
      unsigned int lineno  = 0;
      unsigned int numop   = 0;
      
      errs() << "In function ";
      errs().write_escaped(F.getName());
      errs() << " we called:\n";
      for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
         BasicBlock &BB = *FI;
         for (BasicBlock::iterator BI = BB.begin(), BE = BB.end(); BI != BE;) {
           Instruction *I = BI++;
           if (isa<CallInst>(I) || isa<InvokeInst>(I)) {
             CallSite CS = CallSite(I);
             Value *V = CS.getCalledValue();
             std::string callee = V->getName().str();
             if(callee.compare(0,18,"pthread_mutex_lock") == 0){
             //   Instruction *I = BI;

                IRBuilder<> IRB(I);                
                
                ++PthreadCallsCounter;
                errs().write_escaped(callee) << "\n";
             
/*                if (MDNode *Dbg = CS->getMetadata(dbgKind)) {
                  DILocation Loc (Dbg);
                  filename = Loc.getDirectory().str() + "/" + Loc.getFilename().str();
                  lineno   = Loc.getLineNumber();
                  errs() << "File: " << filename << " Lineno: " << lineno << "\n"; */
                  Value * LineNumber = ConstantInt::get (IntegerType::get (F.getContext(),32), PthreadCallsCounter);
                  
                  Function *FP = cast<Function>(V);
                  FunctionType *FPTy = FP->getFunctionType();
                  std::vector<Type*> Params(FPTy->param_begin(), FPTy->param_end());
                  Params.push_back(IntegerType::get (F.getContext(),32));
                  
                  ArrayRef<Type*> AParams = ArrayRef<Type*>(Params);
                  
                  FunctionType *NFPTy = FunctionType::get(FP->getReturnType(), AParams, FPTy->isVarArg());
                  AttrListPtr PAL = FP->getAttributes().addAttr(Params.size(), Attributes(Attribute::InReg));                  
                  
                  IRBuilder<> IRBB(F.getParent()->getContext());                  
                  Value *FPthread = F.getParent()->getOrInsertFunction("pthread_mutex_lock_ov", NFPTy, PAL);
//                  Value *FPthread = F.getParent()->getOrInsertFunction("pthread_mutex_lock_ov", FP->getFunctionType(), FP->getAttributes());
                  
                  std::vector<Value*> Args(CS.arg_begin(), CS.arg_end());
                  Args.push_back(LineNumber);
                                
                  CallInst *New = CallInst::Create(FPthread,  ArrayRef<Value*>(Args), "", BI);
                  I->eraseFromParent();
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
       ofile << PthreadCallsCounter;
       ofile.close();
          return true;
    }
/*    
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    }
*/
  };
}

char Mutation::ID = 0;
static RegisterPass<Mutation> X("mutation", "Mutation for pThreads");
