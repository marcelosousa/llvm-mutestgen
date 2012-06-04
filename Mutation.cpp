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
#include "llvm/Analysis/DebugInfo.h"

using namespace llvm;

STATISTIC(PthreadCallsCounter, "Counts number of pthread functions called");
  
namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Mutation : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Mutation() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      unsigned dbgKind = F.getContext().getMDKindID("dbg");
      std::string filename = "<unknown>";
      unsigned int lineno  = 0;
      
      errs() << "In function ";
      errs().write_escaped(F.getName());
      errs() << " we called:\n";
      for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ++FI) {
         BasicBlock &BB = *FI;
         for (BasicBlock::iterator BI = BB.begin(), BE = BB.end(); BI != BE; ++BI) {
           if (isa<CallInst>(BI) || isa<InvokeInst>(BI)) {
//             Instruction *I = BI;
             CallSite CS = CallSite(BI);
             Value *V = CS.getCalledValue();
             std::string callee = V->getName().str();
             
             if(callee.compare(0,7,"pthread") == 0){
                ++PthreadCallsCounter;
                errs().write_escaped(callee) << "\n";
             
                if (MDNode *Dbg = CS->getMetadata(dbgKind)) {
                  DILocation Loc (Dbg);
                  filename = Loc.getDirectory().str() + "/" + Loc.getFilename().str();
                  lineno   = Loc.getLineNumber();
                  errs() << "File: " << filename << "\n";
                  errs() << "Lineno: " << lineno << "\n";
                }
             }
/*             if(V->hasOneUse()){
                errs() << " has one use\n";
             }else{
                errs() << " has multiple uses\n";
            }
*/             
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
