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

Translation translate;
int uniqueVertexCount = 0;

void showGraphe(Matrice2D adjacence){    
    std::ofstream output;
    output.open("Graphe.ps",std::ios::out);
    output << "%!PS-Adobe-3.0" << std::endl;
    output << std::endl;  

    for(int x = 0; x < uniqueVertexCount; x++){
        int max = 1;
        for(int y = 0; y < max; y++){
            if(adjacence[x][y] == 1){
                output << x*10 << " " << y*10 << " 1 0 360 arc" <<std::endl;
                output << "0 setgray" << std::endl;
                output << "fill" << std::endl;
                output << "stroke" << std::endl;
                output << std::endl;
            }
        }
        max+=1;
    } 
    output << std::endl;  
}


int translateVertex(Translation translate, int vertex){
    if (translate.find(vertex) != translate.end()){
        std::cout << "founded" << std::endl;
        return translate[vertex];
    }else{
        translate.insert(std::pair<int, int>(vertex, uniqueVertexCount));
        //translate[input]=uniqueVertexCount;
        uniqueVertexCount+=1;
        std::cout << "notfounded" << std::endl;
        return translate[vertex];
    }
}

int numberOfUniqueVertex(char fileUri[]){
    std::ifstream infile(fileUri);

    int vertexA, vertexB;

    while (infile >> vertexA >> vertexB){
        translateVertex(translate,vertexA);
        translateVertex(translate,vertexB);
        std::cout << vertexA << " " << vertexB << " " << uniqueVertexCount << " " << std::endl;

    }

    return uniqueVertexCount;
}

void fillMatrice(char fileUri[], Matrice2D adjacence){
    std::ifstream infile(fileUri);

    int vertexA, vertexB;

    while (infile >> vertexA >> vertexB){

        vertexA = translateVertex(translate,vertexA);
        vertexB = translateVertex(translate,vertexB);
        std::cout << vertexA << " " << vertexB << " " << uniqueVertexCount << " " << std::endl;
        adjacence[vertexA][vertexB] = 1;
        adjacence[vertexB][vertexA] = 1;
    }
}


int main(){
    char fileUri[] = "random.txt";

    uniqueVertexCount = 0;
    numberOfUniqueVertex(fileUri);

    Matrice2D adjacence(uniqueVertexCount,Matrice1D(uniqueVertexCount)); 
    fillMatrice(fileUri,adjacence);

    showGraphe(adjacence);
    return 0;
}