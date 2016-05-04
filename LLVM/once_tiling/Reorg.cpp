#define DEBUG_TYPE "reorg"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/BasicBlock.h"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/InstructionSimplify.h"
using namespace llvm;

STATISTIC(ReorgCounter,"Counts number of functions greeted");

namespace {
	struct Reorg : public ModulePass {
		static char ID;
		Reorg() : ModulePass(ID) {}

		virtual bool runOnModule(Module &M) {
			++ReorgCounter;
			errs() << "Reorg:" << "\n";
			//errs().write_escaped(M.getName()) << '\n';

			LLVMContext &context = llvm::getGlobalContext();
			//insert new basicblock to function sgemm()
			Function* F1 = M.getFunction("trisolv");
			Function* reorgA = M.getFunction("get_ins_comsuption");
			Function* reorgB = M.getFunction("get_tile_size");
                        Function* reorgC = M.getFunction("init");
                        Function* reorgD = M.getFunction("getid");
                        Function* reorgE = M.getFunction("ave");
                        Function* reorgF = M.getFunction("get_start");
                        Function* reorgG = M.getFunction("set_end");
                //        Function* reorgA = M.getFunction("reorgA");
                //        Function* reorgB = M.getFunction("reorgB");
			//get the loopvariables and loop inc steps, store in the vectors
			SmallVector<llvm::Value *, 9> loopvar;
			SmallVector<llvm::Value *, 9> loopinc;
			SmallVector<llvm::Value *, 3> arrayvar;
			Value *v, *inc;
			
		       	llvm::Value* NB = llvm::ConstantInt::get( context , llvm::APInt(64,(uint64_t)128,false ));
                        llvm::Value* NB2 = llvm::ConstantInt::get( context , llvm::APInt(64,(uint64_t)127,false ));
                         
                        GlobalVariable *gv1=M.getNamedGlobal("T2t1");
                        /*GlobalVariable *gv2=M.getNamedGlobal("sgemm.T2t2");
                        GlobalVariable *gv3=M.getNamedGlobal("sgemm.T2t3");
                         // Constant Definitions
                        // ConstantPointerNull* const_ptr_2 = ConstantPointerNull::get(PointerTy_0);*/
                        llvm::Constant * N=llvm::ConstantInt::get( context , llvm::APInt(32,(uint64_t)64,false ));
                        errs() <<"t2:"<< *gv1->getType()->getElementType()<<"\n";
                        errs() <<"t1:"<< *N->getType()<<"\n";
                         // Global Variable Definitions
                     //   gv1->setInitializer(N);
                     //   gv2->setInitializer(N);
                     //   gv3->setInitializer(N);
		        /*
                        int count_loop=0;
                	int count_array=0,count_inc=0,count_var=0;
			for(Function::iterator FI = F1->begin(),FE = F1->end();FI != FE; ++FI) {
				for(BasicBlock::iterator BI = FI->begin(),BE = FI->end(); BI != BE; ++BI) {
					if(!strcmp(BI->getOpcodeName(),"add") && !(BI->getParent()->getName().str().find("polly.loop_header"))){
						if(count_loop<3)
							BI->setOperand(1,NB);
						v = BI->getOperand(0);
						inc = BI->getOperand(1);
						loopvar.push_back(v);
						loopinc.push_back(inc);
						count_loop++;
						break;
					}
					if(!strcmp(BI->getOpcodeName(),"getelementptr") && !(BI->getParent()->getName().str().find("polly.stmt.for.body")) ){
						v = BI->getOperand(0);
						arrayvar.push_back(v);
					}
				}
			}
                        errs() << "Reorg for learn:" << "\n";
			for(int i=0;i<loopinc.size();i++) 
				errs() << *loopvar.operator[](i) <<"hello\n" << *loopinc.operator[](i) << "\n";
			for(int i=0;i<arrayvar.size();i++) 
				errs() << *arrayvar.operator[](i) <<"hello2\n" ;
						
			int index_a = 1, index_b = 2;
			Value *A_a = arrayvar.operator[](1);
			Value *A_b = arrayvar.operator[](2);
			//Value *t1 = dyn_cast<llvm::ConstantInt>(loopinc.operator[](8));
			Function::arg_iterator arg1 = reorgA->arg_begin();
			Value *t1 = ConstantInt::get(Type::getInt32Ty(context),dyn_cast<llvm::ConstantInt>(loopinc.operator[](0))->getSExtValue());
			Value *t2 = ConstantInt::get(Type::getInt32Ty(context),dyn_cast<llvm::ConstantInt>(loopinc.operator[](3))->getSExtValue());
                      errs() << "test the value:" << "\n";
                      errs() <<"t1:"<< *t1<<"\n";
                      errs() <<"t2:"<< *t2<<"\n";
                       */
/*************************************************************************************************************************/                
			Value *a,*b;
			if(F1 && reorgA && reorgB) {
				Function::iterator BI = F1->begin();
				BasicBlock *entryBB = F1->begin();
				BasicBlock* callblock = BasicBlock::Create(context,"copy",F1,entryBB);
				IRBuilder<> builder2(callblock);
                                Value *Ten = builder2.getInt32(10);
                                Value *One = builder2.getInt32(1);
		                Value * cc=builder2.CreateCall(reorgA);//get the instant consumption
                                errs() <<"the cc is:"<< *cc<<"\n";
			       
                                Value *ts= builder2.CreateCall2(reorgB,cc ,Ten);//get the tile_size
                                errs() <<"the ts is:"<< *ts<<"\n";
                             
                                Value *t1= builder2.CreateCall(reorgC,ts);//change global vaviable T2t1
                                builder2.CreateBr(entryBB);    
                             //   llvm::Constant *t2=cast<Constant>(ts);
                                //  errs() <<"the ts type is:"<< *t2->getType()<<"\n";
                               // gv1->setInitializer(t2);
                               // gv2->setInitializer(N);
                               // gv3->setInitializer(N);
                       //         builder2.CreateCall2(reorgA,t1,t2);
		       //	builder2.CreateCall2(reorgB, t1, t2);
/*************************************************************************************************************************/
/*****************************************the part for have loop 't'******************************************************/
/*		         if(F1 && reorgA && reorgB) {       
                                 Function::iterator BI1 = F1->begin();
                                 BasicBlock *entryBB1 = F1->begin();
                                 BasicBlock* callblock2 = BasicBlock::Create(context,"copy",F1,entryBB1);
                                 IRBuilder<> builder3(callblock2);
                                 Value *Ten2 = builder3.getInt32(10);
                                 Value *One2 = builder3.getInt32(1);
                                 Value * aa=builder3.CreateCall(reorgD);//get the process id
                                 Value * cc2=builder3.CreateCall(reorgF,aa);//get the helper thread started
                                 builder3.CreateBr(entryBB1);    

		                int n=0,m=0;
                                Value *v;
	     		
                                
                                IRBuilder<> builder(context);
                                for(Function::iterator FI = F1->begin(),FE = F1->end();FI != FE; ++FI) {
                              
                                for(BasicBlock::iterator BI = FI->begin(),BE = FI->end(); BI != BE; ++BI) {
                                if(!strcmp(BI->getOpcodeName(),"icmp")&&!(BI->getParent()->getName().str().find("for.cond"))&&m==0){
                                        v = BI->getOperand(0);
                                        m=1;
                                        break;
                                }
                               // Value *vv = ConstantInt::get(Type::getInt32Ty(context),dyn_cast<llvm::ConstantInt>(v)->getSExtValue());
				if(!strcmp(BI->getOpcodeName(),"br")&&!(BI->getParent()->getName().str().find("for.body"))&&n==0) {
					builder.SetInsertPoint(&*BI);
		      //			Value * aa=builder.CreateCall(reorgD);
                                        Value * bb=builder.CreateCall(reorgE,v);//the if's t=0 or not
                                        Value *ts1= builder.CreateCall2(reorgB,bb ,Ten2);//get the tile_size
                                        errs() <<"the ts1 is:"<< *ts1<<"\n";
                             
                                        Value *t11= builder.CreateCall(reorgC,ts1);//change global vaviable T2t1
                                        n=1;
                                        break;
		            		}
			
                                 
  
                                 }
                              
                           
                          }
                                  int x=0;
                                  IRBuilder<> builder0(context);
                                for(Function::iterator FI = F1->begin(),FE = F1->end();FI != FE; ++FI) {
                               
                                for(BasicBlock::iterator BI = FI->begin(),BE = FI->end(); BI != BE; ++BI) {
                             
                                if(!strcmp(BI->getOpcodeName(),"ret")&&!(BI->getParent()->getName().str().find("for.end"))&&x==0){
                                         builder0.SetInsertPoint(&*BI);
                                         Value * ab=builder0.CreateCall(reorgG);
                                         x=1;
                                         errs() <<"the cc is:why\n";
                                         break;
                                 }
                               }
                              }*/
/**************************************************************************************************************************/                    
                                        
			} else {
				if(!F1)
				errs() << "No sgemm()\n";
				else if (!reorgA)
					errs() << "No reorgA()\n";
				else
					errs() << "No reorgB()\n";
			}
		        /*
			IRBuilder<> builder(context);
			BasicBlock *bb;
			for(inst_iterator I = inst_begin(F1),E=inst_end(F1); I != E; ++I) {
				if(!strcmp(I->getOpcodeName(),"getelementptr") && !(I->getParent()->getName().str().find("polly.stmt.for.body"))) {
					bb=I->getParent();
				}
			}
			//errs() << bb->getName() << "\n";
			//Value *var_ib = loopvar.operator[](0);
			int flag=0;
			int count = 0;
			Value *N,*var_N;
//			Value *var_N = ConstantInt::get(Type::getInt64Ty(context),640);
			for(BasicBlock::iterator BI = bb->begin(),BE = bb->end(); BI != BE; ++BI) {
			/*	if((dyn_cast<llvm::LoadInst> (&*BI))&& flag < 2) {
					flag++;
					if(flag == 2)
						N = BI->getOperand(0);
				}*/
				
			/*zyl	if(llvm::GetElementPtrInst *gep = dyn_cast<llvm::GetElementPtrInst> (&*BI)) {
					count++;
					if(count==1) {
						PointerType *PTy = dyn_cast<PointerType>( BI->getOperand(0)->getType());
						ArrayType *VTy = dyn_cast<ArrayType>(PTy->getElementType());
						if(VTy) {
							var_N = ConstantInt::get(Type::getInt64Ty(context), VTy->getNumElements());
						}
						else
							errs() << "No\n";
					}
					if(count==2 ){
						
						builder.SetInsertPoint(&*BI);

						Value *var_ib = loopvar.operator[](0);
						Value *var_kb = loopvar.operator[](2);
						Value *var_ii = loopvar.operator[](3);
						Value *var_kk = loopvar.operator[](5);
						Value *var_i = loopvar.operator[](6);
						Value *var_k = loopvar.operator[](8);
						Value *inc_IB = loopinc.operator[](0);
						Value *inc_KB = loopinc.operator[](2);
						Value *inc_iB = loopinc.operator[](3);
						Value *inc_kB = loopinc.operator[](5);
						
						Value *tmp15 = builder.CreateBinOp(Instruction::Mul,var_ib,var_N,"tmp15");
						Value *tmp16 = builder.CreateBinOp(Instruction::Mul,var_kb,inc_IB,"tmp16");
						Value *tmp17 = builder.CreateBinOp(Instruction::Add,tmp15,tmp16,"tmp17");
						Value *tmp18 = builder.CreateBinOp(Instruction::Sub,var_ii,var_ib,"tmp18");
						Value *tmp19 = builder.CreateBinOp(Instruction::Mul,tmp18,inc_KB,"tmp19");
						Value *tmp20 = builder.CreateBinOp(Instruction::Add,tmp17,tmp19,"tmp20");
						Value *tmp21 = builder.CreateBinOp(Instruction::Sub,var_kk,var_kb,"tmp21");
						Value *tmp22 = builder.CreateBinOp(Instruction::Mul,tmp21,inc_iB,"tmp22");
						Value *tmp23 = builder.CreateBinOp(Instruction::Add,tmp20,tmp22,"tmp23");
						Value *tmp24 = builder.CreateBinOp(Instruction::Sub,var_i,var_ii,"tmp24");
						Value *tmp25 = builder.CreateBinOp(Instruction::Mul,tmp24,inc_kB,"tmp25");
						Value *tmp26 = builder.CreateBinOp(Instruction::Add,tmp23,tmp25,"tmp26");
						Value *tmp27 = builder.CreateBinOp(Instruction::Sub,var_k,var_kk,"tmp27");
						Value *tmp28 = builder.CreateBinOp(Instruction::Add,tmp26,tmp27,"tmp28");
					
						Value *new_i = builder.CreateBinOp(Instruction::UDiv,tmp28,var_N,"new_i");
						Value *tmp_n = builder.CreateBinOp(Instruction::Mul,new_i,var_N,"tmp_n");
						Value *new_k = builder.CreateBinOp(Instruction::Sub,tmp28,tmp_n,"new_k");
						//BI->setOperand(0,a);
						BI->setOperand(2,new_i);
						BI->setOperand(3,new_k);
					}
					else if(count==3 ) {
						builder.SetInsertPoint(&*BI);
						Value *var_jb = loopvar.operator[](1);
						Value *var_kb = loopvar.operator[](2);
						Value *var_jj = loopvar.operator[](4);
						Value *var_kk = loopvar.operator[](5);
						Value *var_j = loopvar.operator[](7);
						Value *var_k = loopvar.operator[](8);
					//	Value *var_N = builder.CreateAlignedLoad(N,4,"var_N");
					   	
						Value *inc_JB = loopinc.operator[](1);
						Value *inc_KB = loopinc.operator[](2);
						Value *inc_jB = loopinc.operator[](4);
						Value *inc_kB = loopinc.operator[](5);
						
						Value *tmp1 = builder.CreateBinOp(Instruction::Mul,var_jb,var_N,"tmp1");
						Value *tmp2 = builder.CreateBinOp(Instruction::Mul,var_kb,inc_JB,"tmp2");
						Value *tmp3 = builder.CreateBinOp(Instruction::Add,tmp1,tmp2,"tmp3");
						Value *tmp4 = builder.CreateBinOp(Instruction::Sub,var_jj,var_jb,"tmp4");
						Value *tmp5 = builder.CreateBinOp(Instruction::Mul,tmp4,inc_KB,"tmp5");
						Value *tmp6 = builder.CreateBinOp(Instruction::Add,tmp3,tmp5,"tmp6");
						Value *tmp7 = builder.CreateBinOp(Instruction::Sub,var_kk,var_kb,"tmp7");
						Value *tmp8 = builder.CreateBinOp(Instruction::Mul,tmp7,inc_jB,"tmp8");
						Value *tmp9 = builder.CreateBinOp(Instruction::Add,tmp6,tmp8,"tmp9");
						Value *tmp10 = builder.CreateBinOp(Instruction::Sub,var_j,var_jj,"tmp10");
						Value *tmp11 = builder.CreateBinOp(Instruction::Mul,tmp10,inc_kB,"tmp11");
						Value *tmp12 = builder.CreateBinOp(Instruction::Add,tmp9,tmp11,"tmp12");
						Value *tmp13 = builder.CreateBinOp(Instruction::Sub,var_k,var_kk,"tmp13");
						Value *tmp14 = builder.CreateBinOp(Instruction::Add,tmp12,tmp13,"tmp14");
					
						Value *new_b_k = builder.CreateBinOp(Instruction::UDiv,tmp14,var_N,"new_b_k");
						Value *tmp_n = builder.CreateBinOp(Instruction::Mul,new_b_k,var_N,"tmp_n");
						Value *new_j = builder.CreateBinOp(Instruction::Sub,tmp14,tmp_n,"new_j");
						//BI->setOperand(0,b);
						BI->setOperand(2,new_b_k);
						BI->setOperand(3,new_j);
						break;
					}
				}
			}
                      zyl */
//			for(BasicBlock::iterator BI = bb->begin(),BE = bb->end(); BI != BE; ++BI) 
//				errs() << *BI << "\n";
//
	//		for(inst_iterator I = inst_begin(F1), E = inst_end(F1); I!=E;++I)
	//			errs() << *I << "\n";
/*			errs() << "--------------- IR ------------------" << "\n";
//			M.dump();
			errs() << "--------------END IR ----------------" << "\n";
*/			
			return true;
		}
	};
}

char Reorg::ID = 0;
static RegisterPass<Reorg> X("reorg","Reorganize pass");
