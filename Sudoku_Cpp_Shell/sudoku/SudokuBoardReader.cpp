#include"SudokuBoardReader.hpp"

SudokuFile readFile(std::string filePath){
    //Get filePath. from path and filename. If path is null,
    //it'll default to the current directory
    
    try{
	std::cout<<"start"<<std::endl;
        std::ifstream file(filePath);
	std::cout<<"readcomplete"<<std::endl;        
	//file.open(filePath);
        SudokuFile sF;
        std::string line;
        int lineCounter = 0;
        
        while(getline(file,line)){
            std::cout<<lineCounter<<std::endl;
            std::vector<std::string> lineParts;// = line.split("\\s+");
            std::cout<<line<<std::endl;
            std::istringstream iss(line);
            while(iss){
                std::string part;
                iss>>part;
                if(part != ""){
                    std::cout<<part<<std::endl;
                    lineParts.push_back(part);
                }
            }
            if(lineCounter == 0){
                sF = setSudokuFileParameters(lineParts);//parameter line: contains p, q, N
            }
            else{
                parseLineOfSudokuBoard(sF, lineParts, lineCounter-1);//obo due to parameters taking up first line
            }
            lineCounter++;
        }
        if(lineCounter == 0){
            std::cout<<"Input file \""<<filePath<<"\" was empty"<<std::endl;
        }
        else if(lineCounter < sF.getN()){
            std::cout<<"Incomplete or Emtpy board for file "<<filePath<<". Please be advised"<<std::endl;
        }
        file.close();
        return sF;
    }
    //    }
    catch (...) {
        throw;
        // TODO Auto-generated catch block
    }
    //Something wrong happened if it reaches here
    return SudokuFile();
}

//helpers
SudokuFile setSudokuFileParameters(std::vector<std::string> params){
    if(params.size() != 3)
        throw std::invalid_argument("Params invalid in file.");
//    int** newBoard = new int*[stoi(params[0])];
//    for(int i = 0; i < stoi(params[0]); ++i)
//        newBoard[i] = new int[stoi(params[0])];
    SudokuFile sf = SudokuFile(stoi(params[0]),stoi(params[1]),stoi(params[2]));
   // sf = SudokuFile(stoi(params[0]),stoi(params[1]),stoi(params[2]),newBoard);
    return sf;
//    sf.setN(stoi(params[0]));
//    sf.setP(stoi(params[1]));
//    sf.setQ(stoi(params[2]));
}

void parseLineOfSudokuBoard(SudokuFile& sf, std::vector<std::string> values, int rowNumber) {
//    std::cout<<"parseLine"<<std::endl;
    //writes values to the row set in param rowNumber
//    if(sf.getBoard() == nullptr){
//        int** newBoard = new int*[sf.getN()];
//        for(int i = 0; i < sf.getN(); ++i)
//            newBoard[i] = new int[sf.getN()];
//        sf.setBoard(newBoard);
//    }
//    std::cout<<"ee"<<std::endl;
    std::vector<std::vector<int> > newBoard = sf.getBoard();
//    std::cout<<"ff"<<std::endl;
    for(int i = 0; i < values.size(); i++){
//        std::cout<<rowNumber<<i<<std::endl;
        //std::cout<<values[i]<<std::endl;
//        std::cout<<odometerToInt(values[i])<<std::endl;
        newBoard[rowNumber][i] = odometerToInt(values[i]);
    }
	sf.setBoard(newBoard);
}
