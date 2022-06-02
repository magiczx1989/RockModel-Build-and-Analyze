// Program of morphological opening of octahedron structural element
// Developed and maintained by Dr. Xiang Zhang


#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>


//   MAIN CLASS PROGRAM

int main() {
 
//         Declaration
            int m = 300 ;              //mesh
            int n = m + 1 ;
            int d = 3 ;                  //size of structure element (must be odd)
            double T = 3 ;           //size of cube
            int Rows = pow(n,3) ; 
            double number ;
            char a ;
            char b, c, e, f, g ,h;
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
            

//   Open file
            std :: ifstream MyFile("................................"); 

//   Read the 1st texts
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
               
//   Read the coordinates
            std::cout << "Read the coordinates" << std::endl;
            std :: vector < std :: vector <double> > COOR ;
            for (int Node = 0 ; Node < Rows ; Node++ ){              
                COOR.push_back(std :: vector <double> () );
                for (int j = 0 ; j < 3 ; j++){
                    if (MyFile){
                        MyFile >> number ;
                                
                        if ( j < 3-1 ){
                            MyFile.get(a) ;
                            MyFile.get(b) ;
                            MyFile.get(c) ;
                            MyFile.get(h) ;
                            MyFile.get(e) ;
                            MyFile.get(f) ;
                            MyFile.get(g) ;
                        }
                    }
                    else {
                         std :: cout << "Error1" << std :: endl ;
                    }
                    COOR[Node].push_back(number) ;
                 }
             } 
                                                      
//   Read the 2nd texts         
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



//   Read the field
             std::cout << "Read the Field " << std::endl ;
             std :: vector < std :: vector < std :: vector < bool  > > > Field ;
             for (int i = 0 ; i < n ; i++ ){
                  Field.push_back(std :: vector < std :: vector <bool> > () );
                  for (int j = 0 ; j < n ; j++){
                       Field[i].push_back(std :: vector <bool> ());
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
           

//   Erosion
              std :: cout << "Start of erosion" << std :: endl ;
              std :: vector < std :: vector < std :: vector < bool > > > erode ;
              for (int i = 0 ; i < n ; i++ ){
              std ::cout << "Erosion step = " << i << std ::endl ;
                  erode.push_back(std :: vector < std :: vector <bool> > () );
                  for (int j = 0 ; j < n ; j++){
                      erode[i].push_back(std :: vector <bool> ());
                      for (int k = 0 ; k < n ; k++){
                          erode[i][j].push_back(false) ;
                      }
                  }
              } 
             

              int dd1 = (d-1)/2 ;
              int dd2 = n-1-(d-1)/2 ;
              for (int i = dd1 ; i <= dd2 ; i++){
                   for (int j = dd1 ; j <= dd2 ; j++){
                        for (int k = dd1 ; k <= dd2 ; k++){
                            
                            bool EndErosion = false ;
                            bool test = true ;
                            for (int m = i-dd1 ; m <= i+dd1 && !EndErosion ; m++){
                                 for (int n = j-dd1 ; n <= j+dd1 && !EndErosion ; n++){
                                      for (int p = k-dd1 ; p <= k+dd1 && !EndErosion ; p++){
                                           int r = m-i ;
                                           int s = n-j ;
                                           int q = p-k ;
                                           if ((abs(r)+abs(s)+abs(q)) <= (d-1)/2){
                                              test = test && Field[m][n][p] ;
                                           }
                                           if (!test){
                                               EndErosion = true ;
                                           }
                                      }
                                 }
                            }
                            if (test == true){
                               erode[i][j][k] = true;
                            }
                        }
                    }  
                }

                std :: cout << "End of erosion" << std :: endl ;

//    Dilation
               std :: cout << "Start of dilation" << std :: endl;
               std :: vector < std :: vector < std :: vector < bool > > > dilat ;
               for (int i = 0 ; i < n ; i++ ){
                   std :: cout << "Dilation step = " << i << std :: endl;
                   dilat.push_back(std :: vector < std :: vector <bool> > () );
                   for (int j = 0 ; j < n ; j++){
                        dilat[i].push_back(std :: vector <bool> ());
                        for (int k = 0 ; k < n ; k++){
                             dilat[i][j].push_back(false) ;
                        }
                   }
               } 
  
  
  
              for (int i = dd1 ; i <= dd2 ; i++){
                     for (int j = dd1 ; j <= dd2 ; j++){
                          for (int k = dd1 ; k <= dd2 ; k++){
                               if ( erode[i][j][k] == true ){
                         
                                   for (int m = i-dd1 ; m <= i+dd1 ; m++){
                                        for (int n = j-dd1 ; n <= j+dd1 ; n++){
                                             for (int p = k-dd1 ; p <= k+dd1 ; p++){
                                                  int r = m-i ;
                                                  int s = n-j ;
                                                  int q = p-k ;
                                                  if ((abs(r)+abs(s)+abs(q)) <= (d-1)/2){
                                                     dilat[m][n][p] = true ;
                                                  }
                                             }
                                        }
                                    }
                               }
   
                          }
                     }
               }
               std :: cout << " End of dilation" << std :: endl; 



//  Calculate total volume
              double Volume;
              double Frac;
              double volume = 0;
              for (int i = 0 ; i < n ; i++){
                    for (int j = 0 ; j < n ; j++){
                         for (int k = 0 ; k < n ; k++){
                              if(dilat[i][j][k] == true){
                                  volume = volume + 1 ;
                              }
                         }
                    }
               }     
               Volume = (volume * pow(T,3)) /pow(n,3);
               Frac = volume / pow(n,3);
               std :: cout << "volumetric fraction for d" << d << "=" << Frac << std::endl ;
               std :: cout << "Volume for d" << d << "=" << Volume << std::endl ;

// Writing
              std :: ofstream outfile("....................................."); 
// Write 1st text
               outfile << ligne1 << std :: endl ;
               outfile << ligne2 << std :: endl ;
               outfile << ligne3 << std :: endl ;
               outfile << ligne4 << std :: endl ;
               outfile << ligne5 << std :: endl ;
               outfile << ligne6 << std :: endl ; 
             
// Write the coordinates             
               for (int i = 0 ; i < Rows ; i++){
                     outfile << COOR[i][0] << "       " << COOR[i][1] << "       " << COOR[i][2] << std :: endl ;
               }
                     
                     
// Write 2nd text                  
               outfile << ligne8 << std :: endl ;
               outfile << ligne9 << std :: endl ;
               outfile << ligne10 << std :: endl ;
               outfile << ligne11 << std :: endl ;


// Write the result
               for (int i = 0 ; i < n ; i++){
                    for (int j = 0 ; j < n ; j++){
                         for (int k = 0 ; k < n ; k++){
                              outfile << dilat[i][j][k] << std :: endl ;
                         }
                    }
               }    


 return 0;
}
