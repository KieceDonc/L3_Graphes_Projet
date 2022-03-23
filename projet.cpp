/*

    CE CODE N'EST PAS ENTIÈREMENT LE MIEN

*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include <sstream>

typedef std::vector<int> Matrice1D;
typedef std::vector<Matrice1D> Matrice2D;
typedef std::map<int, int> Translation;

Matrice2D adjacence;
Translation translate;
int uniqueVertexCount = 0;

void showGraphe(){    
    std::ofstream output;
    output.open("Graphe.ps",std::ios::out);
    output << "%!PS-Adobe-3.0" << std::endl;
    output << std::endl;  

    int max = 1;
    for(int x = 0; x < uniqueVertexCount; x++){       
        for(int y = 0; y < max; y++){
            std::cout << adjacence[x][y] << " ";

            if(adjacence[x][y] == 1){
                std::cout << "yes yes yes " << std::endl;
                output << x*10 << " " << y*10 << " 1 0 360 arc" <<std::endl;
                output << "0 setgray" << std::endl;
                output << "fill" << std::endl;
                output << "stroke" << std::endl;
                output << x*10 << " " << y*10 << " moveto" << std::endl;
                output << x*10 << " " << y*10 << " lineto" << std::endl;
                output << std::endl;
            }
        }
        std::cout << "max = "<< max << std::endl;
        max+=1;
    } 
    output << std::endl;  
}


int translateVertex(int vertex){
    if (translate.find(vertex) != translate.end()){
        return translate[vertex];
    }else{
        translate.insert(std::pair<int, int>(vertex, uniqueVertexCount));
        uniqueVertexCount+=1;
        return translate[vertex];
    }
}

int numberOfUniqueVertex(char fileUri[]){
    std::ifstream infile(fileUri);

    int vertexA, vertexB;

    while (infile >> vertexA >> vertexB){
        translateVertex(vertexA);
        translateVertex(vertexB);
    }

    return uniqueVertexCount;
}

void fillMatrice(char fileUri[]){
    std::ifstream infile(fileUri);

    int vertexA, vertexB;

    while (infile >> vertexA >> vertexB){

        vertexA = translateVertex(vertexA);
        vertexB = translateVertex(vertexB);
        adjacence[vertexA][vertexB] = 1;
        adjacence[vertexB][vertexA] = 1;
    }
}


int main(){
    char fileUri[] = "random.txt";

    uniqueVertexCount = 0;
    numberOfUniqueVertex(fileUri);

    adjacence = Matrice2D(uniqueVertexCount,Matrice1D(uniqueVertexCount)); 
    fillMatrice(fileUri);

    showGraphe();
    return 0;
}