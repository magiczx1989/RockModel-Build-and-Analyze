// Program for biphasic change on continous random field, "1" for pore , "0" for matrix
// Developed and maintained by Dr. Xiang Zhang

#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>


// MAIN CLASS PROGRAM

       

int main() {
 
//         Declaration
            int m = 300 ;                           //mesh
            int n = m + 1 ;
            double T = 3.0 ;                      //Size of cube
            int Rows = pow(n,3) ; 
            double number ;
            char a ; 
            std :: string ligne1 ;
            std :: string ligne2 ;
            std :: string ligne3 ;
            std :: string ligne4 ;
            std :: string ligne5 ;
            std :: string ligne6 ;
            std :: string ligne7 ;
            std :: string ligne8 ;
            std :: string ligne9 ;
            std :: string ligne10 ;
            std :: string ligne11 ;
            double threshold = -1.695 ;     //threshold

            
           
//         Open RF file
            std :: ifstream MyFile("............"); 

//         Read the 1st texts
            if (MyFile){
                getline(MyFile, ligne1);
                getline(MyFile, ligne2);
                getline(MyFile, ligne3);
                getline(MyFile, ligne4);
                getline(MyFile, ligne5);
                getline(MyFile, ligne6);
            }
            else{
                std :: cout << "Error0" << std :: endl ;
            }
               
           
 //        Read the coordinates
            std :: vector < std :: vector <double> > COOR ;
            for (int Node = 0 ; Node < Rows ; Node++ ){
                COOR.push_back(std :: vector <double> () );
                for (int j = 0 ; j < 3 ; j++){
                    if (MyFile){
                        MyFile >> number ;
                                
                        if ( j < 3-1 ){
                            MyFile.get(a) ;
                        }
                    }
                    else {
                         std :: cout << "Error1" << std :: endl ;
                    }
                    COOR[Node].push_back(number) ;
                 }
             } 
                         
                                     
 //        Read the 2nd texts
            if (MyFile) {
                 getline(MyFile, ligne7);
                 getline(MyFile, ligne8);
                 getline(MyFile, ligne9);
                 getline(MyFile, ligne10);
                 getline(MyFile, ligne11);
             }
             else {
                   std :: cout << "Error2" << std :: endl ;
             }



//          Read the field
             std :: vector < std :: vector < std :: vector < double  > > > Field ;
             for (int i = 0 ; i < n ; i++ ){
                  Field.push_back(std :: vector < std :: vector <double> > () );
                  for (int j = 0 ; j < n ; j++){
                       Field[i].push_back(std :: vector <double> ());
                       for (int k = 0 ; k < n ; k++){
                            if (MyFile){
                                MyFile >> number ;
                            }
                            else {
                                 std :: cout << "Error3" << std :: endl ;
                            }
                            Field[i][j].push_back(number) ;
                        }
                   }
              } 
           

//           Biphasic Change
              std::cout << "Start Biphasic Change" << std :: endl;
              for (int i = 0 ; i < n ; i++){
                   for (int j = 0 ; j < n ; j++){
                       for (int k = 0 ; k < n ; k++){
                           if (Field[i][j][k] < threshold){
                               Field[i][j][k] = true ;
                           }
                           else{
                                Field[i][j][k] = false ;
                           }
                       }
                   }
              }  

//           Calculate  volume
              double Volume;
              double Frac;
              double volume = 0;
              for (int i = 0 ; i < n ; i++){
                   for (int j = 0 ; j < n ; j++){
                       for (int k = 0 ; k < n ; k++){
                           if (Field[i][j][k] == true){
                               volume = volume + 1 ;
                           }
                       }
                   }
              }    
              Volume = (volume * pow(T,3))/pow(n,3);
              Frac = volume / pow(n,3);
              std :: cout << "Volumetric Fraction" << Frac << std::endl ;
              std :: cout << "Volume" << Volume << std::endl ;

//            Writing
               std :: ofstream outfile(".................."); 

//            Write 1st texts
               outfile << ligne1 << std :: endl ;
               outfile << ligne2 << std :: endl ;
               outfile << ligne3 << std :: endl ;
               outfile << ligne4 << std :: endl ;
               outfile << ligne5 << std :: endl ;
               outfile << ligne6 << std :: endl ; 
             
//            Write the coordinates             
               for (int i = 0 ; i < Rows ; i++){
                     outfile << COOR[i][0] << "       " << COOR[i][1] << "       " << COOR[i][2] << std :: endl ;
               }
                     
                     
//            Write 2nd texts        
               outfile << ligne8 << std :: endl ;
               outfile << ligne9 << std :: endl ;
               outfile << ligne10 << std :: endl ;
               outfile << ligne11 << std :: endl ;


//            Write the Biphasic Field
               for (int i = 0 ; i < n ; i++){
                    for (int j = 0 ; j < n ; j++){
                         for (int k = 0 ; k < n ; k++){
                              outfile << Field[i][j][k] << std :: endl ;
                         }
                    }
               }             
              


 return 0;
}

