#include"Converter.hpp"

ConstraintNetwork SudokuFileToConstraintNetwork(SudokuFile sf){
    std::vector<std::vector<int> > board = sf.getBoard();
  
    std::vector<Variable*> variables;
    int value = 0;

    for (int i =0;i<sf.getN(); i++){
		for (int j=0;j<sf.getN();j++){
	    	value = board[i][j];
//			std::cout<<"value:"<<value<<std::endl;
	    	std::vector<int> domain;
	    	if (value == 0){
				for (int d=1; d<=sf.getN(); d++){
		    		domain.push_back(d);
				}	
	    	}	
	    	else{
				domain.push_back(value);
	    	}
	    	int block = (i/sf.getP() * sf.getP()+j/sf.getQ());
	    	Variable* toPushBack = new Variable(domain,i,j,block);
			variables.push_back(toPushBack);
		}
	}

    std::map<int, std::vector<Variable*> > rows;
    std::map<int, std::vector<Variable*> > cols;
    std::map<int, std::vector<Variable*> > blocks;

    for (Variable* v:variables){
		int row = v->row();
		int col = v->col();
		int block = v->block();
//		std::vector<Variable*> n;
		if (!rows.count(row)){
	    	rows[row]= std::vector<Variable*>();
		}
		if (!cols.count(col)){
	    	cols[col] = std::vector<Variable*>();
		}
		if (!blocks.count(block)){
		    blocks[block] = std::vector<Variable*>();
		}
		rows[row].push_back(v);
		cols[col].push_back(v);
		blocks[block].push_back(v);
	}
    ConstraintNetwork cn = ConstraintNetwork();
//    std::cout<<"oriSize"<<std::endl;
	for (Variable* v : variables){
//		std::cout<<v->size();
		cn.add(v);
    }
//	std::cout<<std::endl<<"afterSize";
//	std::cout<<std::endl;
    for (auto iterator = rows.begin();iterator!=rows.end();iterator++){
		Constraint c = Constraint();
		for (Variable* vv:iterator->second){
		    c.addVariable(vv);
		}
//		std::cout<<"size"<<c.size()<<std::endl;
		cn.add(c);
    }
    for (auto iterator = cols.begin();iterator!=cols.end();iterator++){
         Constraint c = Constraint();
         for (Variable* vv:iterator->second){
            c.addVariable(vv);
         }
         cn.add(c);
     }
     for (auto iterator = blocks.begin();iterator!=blocks.end();iterator++){
         Constraint c = Constraint();
         for (Variable* vv:iterator->second){
             c.addVariable(vv);
         }
         cn.add(c);
      }
//	  if(!cn.isConsistent())
//	      std::cout<<"Error"<<std::endl;
//	std::cout<<"test ori"<<std::endl;
//	for(Variable* v : cn.getVariables()){
//		std::cout<<v->getAssignment()<<";;"<<v<<std::endl;
//	}
    return cn;
}

SudokuFile ConstraintNetworkToSudokuFile(ConstraintNetwork cn, int n, int p, int q){
    SudokuFile sf = SudokuFile();
  //  std::cout<<"aa"<<std::endl;
    std::vector<std::vector<int> > board;// = new int* [n];
//	std::cout<<"aa"<<std::endl;
    for(int i = 0; i < n; ++i){
        std::vector<int> line;
		for(int j = 0; j < n; ++j)
			line.push_back(0);
		board.push_back(line);
		//board[i] = new int[n];
	}
//    std::cout<<"aa"<<std::endl;
    int row = 0, col = 0;
    for (Variable* v: cn.getVariables()){
//        std::cout<<row<<" "<<col<<std::endl;
 //       std::cout<<v.getAssignment()<<std::endl;
// 		std::cout<<"v->getAssignment(): "<<v->getAssignment()<<std::endl;
        board[row++][col] = v->getAssignment();
//        std::cout<<row<<" "<<col<<std::endl;
        if(row==n){
            row = 0;
            col++;
        }
    }
//    std::cout<<"aa"<<std::endl;
    sf.setBoard(board);
//    std::cout<<"aa"<<std::endl;
    sf.setN(n);
    sf.setP(p);
    sf.setQ(q);
    //std::cout<<sf.toString()<<std::endl;
    return sf;
}
