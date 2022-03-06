#ifndef PRODUCTPROCESSINGELEMENTCOMMAND_H_INCLUDED
#define PRODUCTPROCESSINGELEMENTCOMMAND_H_INCLUDED

//:public Command
class ProductProcessingElementCommand {
public:
	ProductProcessingElementCommand();

	ProductProcessingElementCommand(ProductProcessingElement * s,  void(ProductProcessingElement::* trPFunc)(Params*), Params *   params){
		_product= s;
		_trPFunc = trPFunc;
		_params = params;

	}
	ProcProductCommand(ProcessedProduct * s=0,  void(ProductProcessingItem::* trFunc)()=0){
        	_product= s;
	    	_trFunc = trFunc;

	}
	virtual ~ProcProductCommand(){}
	virtual void execute();
	virtual void undo(){}
    //returns changed state product
	ProcessedProduct * getProduct(){ return _product; }

protected:
	ProcessedProduct * _product;
  void (ProcessedProduct::*_trFunc)();
  void (ProcessedProduct::*_trPFunc)(Params *);

   Params * _params;
};


#endif // PRODUCTPROCESSINGELEMENTCOMMAND_H_INCLUDED
