// Program to find the transfer paths between two opposite faces
// Developed and maintained by Dr. Xiang Zhang

#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <set>
#include <iterator>

// MAIN CLASS PROGRAM


int main() {
    
// Declaration
    int m = 300 ;                  //mesh
    int n = m + 1 ;
    double T = 3 ;                //size of cube
    int d = 3;
    int Rows = pow(n,3) ;
    double number;
    
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
    
 
// Open file of biphasic field
    std :: ifstream MyFile("..........................."); 

// Read the 1st texts
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
    
// Read the coordinates
    std::cout << "START READ COORDINATE" << std::endl;
    std::time_t result1 = std::time(NULL);
    std::cout << std::asctime(std::localtime(&result1)) << std::endl;
    
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
    
// Read the 2nd texts
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
    
// Read the field
    std::cout << "START READ FIELD" << std::endl;
    std::time_t result2 = std::time(NULL);
    std::cout << std::asctime(std::localtime(&result2)) << std::endl;
    
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
    
    
// Define the bord 1
    std::cout << "START DEFINITION OF PORES ON BORD 1" << std::endl;
    std::time_t result3 = std::time(NULL);
    std::cout << std::asctime(std::localtime(&result3)) << std::endl;
    
    std :: vector < std :: vector < std :: vector < bool  > > > bord1 ;
    for (int i = 0 ; i < n ; i++ ){
        bord1.push_back(std :: vector < std :: vector <bool> > () );
        for (int j = 0 ; j < n ; j++){
            bord1[i].push_back(std :: vector <bool> ());
            for (int k = 0 ; k < n ; k++){
                bord1[i][j].push_back(false) ;
            }
        }
    }
    
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                if (k == (n-1))                                                                       //change the direction
                    bord1[i][j][k] = true;
            }
        }
    }
 
// Intersection bord1 and initial field (define pores on bord1)
    std :: vector < std :: vector < std :: vector < bool > > > bordporosity1 ;
    for (int i = 0 ; i < n ; i++ ){
        bordporosity1.push_back(std :: vector < std :: vector <bool> > () );
        for (int j = 0 ; j < n ; j++){
            bordporosity1[i].push_back(std :: vector <bool> ());
            for (int k = 0 ; k < n ; k++){
                bordporosity1[i][j].push_back(false) ;
            }
        }
    }
    
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                bordporosity1[i][j][k] = Field[i][j][k] && bord1[i][j][k];
            }
        }
    }
    
    std::cout << "END DEFINITION OF PORES ON BORD1" << std::endl;
    std::time_t result4 = std::time(NULL);
    std::cout << std::asctime(std::localtime(&result4)) << std::endl;

    
// First step of geodesic distance from bord1
    std :: vector < std :: vector < std :: vector < int  > > > distancegeodesic1 ;
    for (int i = 0 ; i < n ; i++ ){
        distancegeodesic1.push_back(std :: vector < std :: vector <int> > () );
        for (int j = 0 ; j < n ; j++){
            distancegeodesic1[i].push_back(std :: vector <int> ());
            for (int k = 0 ; k < n ; k++){
                distancegeodesic1[i][j].push_back(0) ;
            }
        }
    }
    
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                if(Field[i][j][k] && bord1[i][j][k] == true){
                    distancegeodesic1[i][j][k] = 1 ;
                }
            }
        }
    }
 

// Declare bordporosity2 for comparison
    std :: vector < std :: vector < std :: vector < bool > > > bordporosity2;
    for (int i = 0 ; i < n ; i++ ){
        bordporosity2.push_back(std :: vector < std :: vector <bool> > () );
        for (int j = 0 ; j < n ; j++){
            bordporosity2[i].push_back(std :: vector <bool> ());
            for (int k = 0 ; k < n ; k++){
                bordporosity2[i][j].push_back(false) ;
            }
        }
    }
    
// Declare a vector for dilatedporosity (Delation)
    std :: vector < std :: vector < std :: vector < bool > > > dilatedbordporosity1 ;
    for (int i = 0 ; i < n ; i++ ){
        dilatedbordporosity1.push_back(std :: vector < std :: vector <bool> > () );
        for (int j = 0 ; j < n ; j++){
            dilatedbordporosity1[i].push_back(std :: vector <bool> ());
            for (int k = 0 ; k < n ; k++){
                dilatedbordporosity1[i][j].push_back(false) ;
            }
        }
    }
    
// Geodesic reconstruction from bord1
    bool B = false ;
    int step = 1 ;
    
    while (B == false){
        std::cout << "START NEW LAYER" << std::endl;
        std::time_t result5 = std::time(NULL);
        std::cout << std::asctime(std::localtime(&result5)) << std::endl;
        
        
// Dilation
        int dd1 = (d-1)/2 ;
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    if ( bordporosity1[i][j][k] == true ){
                        
                        for (int v = i-dd1 ; v <= i+dd1 ; v++){
                            for (int w = j-dd1 ; w <= j+dd1 ; w++){
                                for (int p = k-dd1 ; p <= k+dd1 ; p++){
                                    if((0 <= v)&&(v < n)&&(0 <= w)&&(w < n)&&(0 <= p)&&(p < n)){
                                        int r = v-i ;
                                        int s = w-j ;
                                        int q = p-k ;
                                        if ((abs(r)+abs(s)+abs(q)) <= (d-1)/2){
                                            dilatedbordporosity1[v][w][p] = true ;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
                
// Intersection dilatedbordporosity1 and field
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    bordporosity2[i][j][k] = Field[i][j][k] && dilatedbordporosity1[i][j][k];
                }
            }
        }


        
// Geodesic Distance
        std :: vector < std :: vector < std :: vector < bool > > > soustraction1 ;
        for (int i = 0 ; i < n ; i++ ){
            soustraction1.push_back(std :: vector < std :: vector <bool> > () );
            for (int j = 0 ; j < n ; j++){
                soustraction1[i].push_back(std :: vector <bool> ());
                for (int k = 0 ; k < n ; k++){
                    soustraction1[i][j].push_back(false) ;
                }
            }
        }
        
        
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    soustraction1[i][j][k] = bordporosity2[i][j][k] - bordporosity1[i][j][k];
                }
            }
        }
        
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    if (soustraction1[i][j][k]==true){
                        distancegeodesic1[i][j][k] = step + 1;
                    }
                }
            }
        }

        
        
// Equality of bordporosity1 and bordporosity2
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    if (bordporosity1[i][j][k] == bordporosity2[i][j][k]){
                        B = true ;
                    }
                    else {
                        B = false;
                        step = step + 1 ;
                        goto stop;
                    }
                }
            }
        }
        
    stop:
        
        if (B == false){
            for (int i = 0 ; i < n ; i++){
                for (int j = 0 ; j < n ; j++){
                    for (int k = 0 ; k < n ; k++){
                        bordporosity1[i][j][k]=bordporosity2[i][j][k];
                    }
                }
            }
        }
        
        
    }
    
// Declare the vector percolation face 1
    std :: vector < std :: vector < std :: vector < bool > > > Percolationface1;
    for (int i = 0 ; i < n ; i++ ){
        Percolationface1.push_back(std :: vector < std :: vector <bool> > () );
        for (int j = 0 ; j < n ; j++){
            Percolationface1[i].push_back(std :: vector <bool> ());
            for (int k = 0 ; k < n ; k++){
                Percolationface1[i][j].push_back(false) ;
            }
        }
    }
    
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                Percolationface1[i][j][k] = bordporosity2[i][j][k];
            }
        }
    }
    
    
     std::cout << "Maximum geodesic distance from bord1 = " << step << std::endl ;
    
    
// Define the bord 2
    std::cout << "START DEFINITION OF PORES ON BORD 2" << std::endl;
    std::time_t result9 = std::time(NULL);
    std::cout << std::asctime(std::localtime(&result9)) << std::endl;
    
    std :: vector < std :: vector < std :: vector < bool  > > > bord2 ;
    for (int i = 0 ; i < n ; i++ ){
        bord2.push_back(std :: vector < std :: vector <bool> > () );
        for (int j = 0 ; j < n ; j++){
            bord2[i].push_back(std :: vector <bool> ());
            for (int k = 0 ; k < n ; k++){
                bord2[i][j].push_back(false) ;
            }
        }
    }
    
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                if (k == 0)                                                                       //change the direction
                    bord2[i][j][k] = true;
            }
        }
    }
    
    
// Intersection bord2 and initial field (define pores on bord2)
   
    for (int i = 0 ; i < n ; i++ ){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                bordporosity1[i][j][k] = false ;
            }
        }
    }
    
    
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                bordporosity1[i][j][k] = Field[i][j][k] && bord2[i][j][k];
            }
        }
    }
    

    std::cout << "END DEFINITION OF PORES ON BORD2" << std::endl;
    std::time_t result10 = std::time(NULL);
    std::cout << std::asctime(std::localtime(&result10)) << std::endl;
    

    
// First step of geodesic distance from bord2
    std :: vector < std :: vector < std :: vector < int  > > > distancegeodesic2 ;
    for (int i = 0 ; i < n ; i++ ){
        distancegeodesic2.push_back(std :: vector < std :: vector <int> > () );
        for (int j = 0 ; j < n ; j++){
            distancegeodesic2[i].push_back(std :: vector <int> ());
            for (int k = 0 ; k < n ; k++){
                distancegeodesic2[i][j].push_back(0) ;
            }
        }
    }
    
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                if(Field[i][j][k] && bord2[i][j][k] == true){
                    distancegeodesic2[i][j][k] = 1 ;
                }
            }
        }
    }


    
// Declare bordporosity2 for comparison
   
    for (int i = 0 ; i < n ; i++ ){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                bordporosity2[i][j][k] = false ;
            }
        }
    }
    
// Declare a vector for dilatedporosity (Delation)

    for (int i = 0 ; i < n ; i++ ){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                dilatedbordporosity1[i][j][k] = false ;
            }
        }
    }
    
// Geodesic reconstruction from bord2
    
    B = false ;
    step = 1 ;
    
    while (B == false){
        std::cout << "START NEW LAYER" << std::endl;
        std::time_t result11 = std::time(NULL);
        std::cout << std::asctime(std::localtime(&result11)) << std::endl;
        
        
// Dilation
        int dd1 = (d-1)/2 ;
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    if ( bordporosity1[i][j][k] == true ){
                        
                        for (int v = i-dd1 ; v <= i+dd1 ; v++){
                            for (int w = j-dd1 ; w <= j+dd1 ; w++){
                                for (int p = k-dd1 ; p <= k+dd1 ; p++){
                                    if((0 <= v)&&(v < n)&&(0 <= w)&&(w < n)&&(0 <= p)&&(p < n)){
                                        int r = v-i ;
                                        int s = w-j ;
                                        int q = p-k ;
                                        if ((abs(r)+abs(s)+abs(q)) <= (d-1)/2){
                                            dilatedbordporosity1[v][w][p] = true ;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
                
        
// Intersection dilatedbordporosity1 and field
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    bordporosity2[i][j][k] = Field[i][j][k] && dilatedbordporosity1[i][j][k];
                }
            }
        }
        
  
// Geodesic Distance
        std :: vector < std :: vector < std :: vector < bool > > > soustraction2 ;
        for (int i = 0 ; i < n ; i++ ){
            soustraction2.push_back(std :: vector < std :: vector <bool> > () );
            for (int j = 0 ; j < n ; j++){
                soustraction2[i].push_back(std :: vector <bool> ());
                for (int k = 0 ; k < n ; k++){
                    soustraction2[i][j].push_back(false) ;
                }
            }
        }
        
        
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    soustraction2[i][j][k] = bordporosity2[i][j][k] - bordporosity1[i][j][k];
                }
            }
        }
        
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    if (soustraction2[i][j][k]==true){
                        distancegeodesic2[i][j][k] = step + 1;
                    }
                }
            }
        }
        
        
// Equality of bordporosity1 and bordporosity2
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    if (bordporosity1[i][j][k]==bordporosity2[i][j][k]){
                        B = true ;
                    }
                    else {
                        B = false;
                        step = step + 1 ;
                        goto stop1;
                    }
                }
            }
        }
        
    stop1:
        
        if (B == false){
            for (int i = 0 ; i < n ; i++){
                for (int j = 0 ; j < n ; j++){
                    for (int k = 0 ; k < n ; k++){
                        bordporosity1[i][j][k]=bordporosity2[i][j][k];
                    }
                }
            }
        }
        
        
    }
    
// Declare the vector percolation face 2
    std :: vector < std :: vector < std :: vector < bool > > > Percolationface2;
    for (int i = 0 ; i < n ; i++ ){
        Percolationface2.push_back(std :: vector < std :: vector <bool> > () );
        for (int j = 0 ; j < n ; j++){
            Percolationface2[i].push_back(std :: vector <bool> ());
            for (int k = 0 ; k < n ; k++){
                Percolationface2[i][j].push_back(false) ;
            }
        }
    }
    
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                Percolationface2[i][j][k]=bordporosity2[i][j][k];
            }
        }
    }
    
     std::cout << "Maximum geodesic distance from bord2 = " << step << std::endl ;

// Declare Percolation
    std :: vector < std :: vector < std :: vector < bool > > > Percolation;
    for (int i = 0 ; i < n ; i++ ){
        Percolation.push_back(std :: vector < std :: vector <bool> > () );
        for (int j = 0 ; j < n ; j++){
            Percolation[i].push_back(std :: vector <bool> ());
            for (int k = 0 ; k < n ; k++){
                Percolation[i][j].push_back(false) ;
            }
        }
    }
    

// Intersection of percolation face1 et percolation face2
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                Percolation[i][j][k] = Percolationface1[i][j][k] && Percolationface2[i][j][k];
            }
        }
    }
   
    std :: vector < std :: vector < std :: vector < int  > > > distancegeodesic ;
        for (int i = 0 ; i < n ; i++ ){
             distancegeodesic.push_back(std :: vector < std :: vector <int> > () );
             for (int j = 0 ; j < n ; j++){
                 distancegeodesic[i].push_back(std :: vector <int> ());
                 for (int k = 0 ; k < n ; k++){
                      distancegeodesic[i][j].push_back(0) ;
                 }
             }
        }
    
// Calculate the volume of percolation 
    double Volume;
    double Frac;
    double volume = 0;
    for (int i = 0 ; i <n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k <n ; k++){
                if (Percolation[i][j][k]==true){
                    volume = volume + 1 ;
                }
            }
        }
    }
    
    Volume = (volume * pow(T,3))/pow(n,3);
    Frac = volume / pow(n,3);
    if (Volume == 0 ){
        std::cout << "Without percolation" << std::endl;
    }
    else {
        std::cout << "Volumetric fraction of the percolation = " << Frac << std::endl;
        std::cout << "Volume of the percolation = " << Volume << std::endl;
        std::cout << "START CALCULATION OF GEODESIC DISTANCE" << std::endl;
        std::time_t result12 = std::time(NULL);
        std::cout << std::asctime(std::localtime(&result12)) << std::endl;
  
      
// Geodesic distance

        for (int i = 0 ; i < n ; i++){
             for (int j = 0 ; j < n ; j++){
                  for (int k = 0 ; k < n ; k++){
                      if(Percolation[i][j][k] && bord1[i][j][k] == true){
                          distancegeodesic[i][j][k] = 1 ;
                      }
                  }
             }
        }
        
//  Intersection bord and percolation
        for (int i = 0 ; i < n ; i++ ){
             for (int j = 0 ; j < n ; j++){
                  for (int k = 0 ; k < n ; k++){
                       bordporosity1[i][j][k] = false ;
                  }
             }
        }
    
    
        for (int i = 0 ; i < n ; i++){
             for (int j = 0 ; j < n ; j++){
                  for (int k = 0 ; k < n ; k++){
                       bordporosity1[i][j][k] = Percolation[i][j][k] && bord1[i][j][k];
                  }
             }
        }
        
     
        for (int i = 0 ; i < n ; i++ ){
             for (int j = 0 ; j < n ; j++){
                  for (int k = 0 ; k < n ; k++){
                        bordporosity2[i][j][k] = false ;
                  }
             }
        }
         
        for (int i = 0 ; i < n ; i++ ){
            for (int j = 0 ; j < n ; j++){
                 for (int k = 0 ; k < n ; k++){
                      dilatedbordporosity1[i][j][k] = false ;
                 }
            }
        }

        B = false ;
        step = 1 ;
    
        while (B == false){
              std::cout << "START NEW LAYER" << std::endl;
              std::time_t result5 = std::time(NULL);
              std::cout << std::asctime(std::localtime(&result5)) << std::endl;
    
        
// Dilation
        int dd1 = (d-1)/2 ;
             for (int i = 0 ; i < n ; i++){
                  for (int j = 0 ; j < n ; j++){
                       for (int k = 0 ; k < n ; k++){
                           if ( bordporosity1[i][j][k] == true ){
                        
                               for (int v = i-dd1 ; v <= i+dd1 ; v++){
                                    for (int w = j-dd1 ; w <= j+dd1 ; w++){
                                         for (int p = k-dd1 ; p <= k+dd1 ; p++){
                                            if((0 <= v)&&(v < n)&&(0 <= w)&&(w < n)&&(0 <= p)&&(p < n)){
                                               int r = v-i ;
                                               int s = w-j ;
                                               int q = p-k ;
                                               if ((abs(r)+abs(s)+abs(q)) <= (d-1)/2){
                                                   dilatedbordporosity1[v][w][p] = true ;
                                               }
                                            }
                                         }
                                    }
                               }
                          }
                      }
                 }
             }
        
        
        
// Intersection dilatedbordporosity1 and percolation
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    bordporosity2[i][j][k] = Percolation[i][j][k] && dilatedbordporosity1[i][j][k];
                }
            }
        }
        


//  Calculate Geodesic Distance
        std :: vector < std :: vector < std :: vector < bool > > > soustraction ;
        for (int i = 0 ; i < n ; i++ ){
            soustraction.push_back(std :: vector < std :: vector <bool> > () );
            for (int j = 0 ; j < n ; j++){
                soustraction[i].push_back(std :: vector <bool> ());
                for (int k = 0 ; k < n ; k++){
                    soustraction[i][j].push_back(false) ;
                }
            }
        }
        
        
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    soustraction[i][j][k] = bordporosity2[i][j][k] - bordporosity1[i][j][k];
                }
            }
        }
        
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    if (soustraction[i][j][k]==true){
                        distancegeodesic[i][j][k] = step + 1;
                    }
                }
            }
        }
        
// Equality of bordporosity1 and bordporosity2
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                for (int k = 0 ; k < n ; k++){
                    if (bordporosity1[i][j][k]==bordporosity2[i][j][k]){
                        B = true ;
                    }
                    else {
                        B = false;
                        step = step + 1 ;
                        goto stop3;
                    }
                }
            }
        }
    
stop3:
        
        if (B == false){
             for (int i = 0 ; i < n ; i++){
                 for (int j = 0 ; j < n ; j++){
                     for (int k = 0 ; k < n ; k++){
                          bordporosity1[i][j][k]=bordporosity2[i][j][k];
                     }
                 }
             }
         }
    
    
      }


        std::cout << "END CALCULATION GEODESIC DISTANCE" << std::endl;
        std::time_t result13 = std::time(NULL);
        std::cout << std::asctime(std::localtime(&result13)) << std::endl;
        std::cout << " Maximum Distance geodesic  = " << step << std::endl;

   }


// Find the min and max distance


    int min = 100000000;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                if (k == 0 && distancegeodesic[i][j][k] < min && distancegeodesic[i][j][k]!= 0)                      //change the direction
                    min = distancegeodesic[i][j][k];
            }
        }
    }


    int max = 0;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                if (k == 0 && distancegeodesic[i][j][k] > max)                                                                      //change the direction
                    max = distancegeodesic[i][j][k];
            }
        }
    }

    
    std::cout << "Maximum Distance geodesic of percolation = " << max << std::endl; 
    std::cout << "Minimum Distance geodesic of percolation = " << min << std::endl;

    
    
// Writing Percolation
    std :: ofstream outfile("........................................");

//Write 1st texts
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
    
    
// Write the 2nd texts
    outfile << ligne8 << std :: endl ;
    outfile << ligne9 << std :: endl ;
    outfile << ligne10 << std :: endl ;
    outfile << ligne11 << std :: endl ;
    
    
// Write the field
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                outfile << Percolation[i][j][k] << std :: endl ;
            }
        }
    }
 

// Writing distance geodesic
    std :: ofstream outfile2("......................"); 

// Write 1st texts
    outfile2 << ligne1 << std :: endl ;
    outfile2 << ligne2 << std :: endl ;
    outfile2 << ligne3 << std :: endl ;
    outfile2 << ligne4 << std :: endl ;
    outfile2 << ligne5 << std :: endl ;
    outfile2 << ligne6 << std :: endl ;
    
// Write the coordinates
    for (int i = 0 ; i < Rows ; i++){
        outfile2 << COOR[i][0] << "       " << COOR[i][1] << "       " << COOR[i][2] << std :: endl ;
    }
    
    
// Write the 2nd texts
    outfile2 << ligne8 << std :: endl ;
    outfile2 << ligne9 << std :: endl ;
    outfile2 << ligne10 << std :: endl ;
    outfile2 << ligne11 << std :: endl ;
    
// Write the field
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            for (int k = 0 ; k < n ; k++){
                outfile2 << distancegeodesic[i][j][k] << std :: endl ;
            }
        }
    }
    

    
    return 0;
}

