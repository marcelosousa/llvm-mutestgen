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
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Value.h"
#include "llvm/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CallSite.h"

using namespace llvm;

STATISTIC(PthreadCallsCounter, "Counts number of pthread functions called");

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Mutation : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Mutation() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      errs() << "In function: ";
      errs().write_escaped(F.getName());
      errs() << "we called:\n";
      for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
         BasicBlock &BB = *FI;
         for (BasicBlock::iterator BI = BB.begin(), BE = BB.end(); BI != BE; ++BI) {
           if (isa<CallInst>(BI) || isa<InvokeInst>(BI)) {
             Instruction *I = BI;
             CallSite CS = CallSite(I);
             Value *V = CS.getCalledValue();
             ++PthreadCallsCounter;
             errs().write_escaped(V->getName());
             if(V->hasOneUse()){
                errs() << " has one use\n";
             }else{
                errs() << " has multiple uses\n";
            }
             
          }
       }
      }
      return false;
    }
    
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    }
  };
}

char Mutation::ID = 0;
static RegisterPass<Mutation> X("mutation", "Mutation for pThreads");
