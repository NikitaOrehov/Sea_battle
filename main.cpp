#include "FIELD/field.h"
#include "PLAYERS/human.h"
#include "PLAYERS/IA.h"


int main(){
    Human human = Human();
    IA ia = IA();
    std::cout<<"Use W A S D to move the ship. Use E to turn the ship. Use the space bar to confirm the coordinates of the ship."<<std::endl;
    human.placement();
    std::cout<<"generation map..."<<std::endl;
    ia.placement();
    while(true){
        system("cls");
        while(true){
            human.PrintInfo();
            std::cout<<"\n";
            std::cout<<"Enter the coordinates(For example, A5): ";
            std::string answer;
            std::cin>>answer;
            try{
                system("cls");
                std::cout<<"you ";
                int motion1 = human.attack(answer, ia);
                if (ia.GetHp() <= 0){
                    std::cout<<"You win"<<std::endl;
                    exit(1);
                }
                if (motion1 == 1){
                    continue;
                }
            }
            catch(const char* messege){
                std::cout<<messege<<std::endl;
                continue;
            }
            while(true){
                    std::cout<<"IA ";
                    int motion2 = ia.attack(answer, human);
                    if (human.GetHp() <= 0){
                        std::cout<<"You lose"<<std::endl;
                        exit(1);
                    }
                    if (motion2 == 1){
                        continue;
                    }
                    else{
                        break;
                    }
                }
        }
    }
}