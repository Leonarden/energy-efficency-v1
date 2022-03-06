
#ifndef ITEMCOMMAND_H_
#define ITEMCOMMAND_H_


//:public Command
class ProductProcessingItemCommand: public ProductProcessingElementCommand {
public:
	ProductProcessingItemCommand();

	ProductProcessingItemCommand(ProductProcessingItem * s,  void(ProductProcessingItem::* trFunc)(), int *  param){
		_product= s;
		_trFunc = trFunc;
		_param = param;

	}
	ProcProductCommand(ProcessedProduct * s=0,  void(ProductProcessingItem::* trFunc)()=0){
		 ProcProductCommand(s,trFunc,nullptr);
		}
	virtual ~ProcProductCommand(){}
	virtual void execute();
	virtual void undo(){}
    //returns changed state product
	ProcessedProduct * getProduct(){ return _product; }

protected:
	ProcessedProduct * _product;
  void (ProcessedProduct::*_trFunc)();
   int * _param;
};







#endif
