#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int health = 100;
int lvl = 0;
int x, y;
int monsterHP = 30;
int level = 1;
int kuld = 0;
bool running = true;

typedef struct
{
    int potions;
} Inventar;

Inventar inventar = {1}; // Annab väärtuse 0 kõigile

int main()
{
    srand(time(NULL));
    char choose;

    printf("Teretulemast Farafelli seiklusele!\n");
    printf("Sattusid dungeonisse, kus on kottpime ja kriiksutavaid hääli on kuulda. Tunned värinaid üle enda keha, aga sa pead väljapääsu otsima\n");

    while (health > 0)
    {
        printf("\nOled asukohal (%d, %d). Kuld %d | Level %d \n", x, y, kuld, level);
        printf("Keybinds: (w=north,a=west,s=south,d=east), q=quit and i=inventar: ");
        scanf(" %c", &choose);

        while (getchar() != '\n')
            ;

        if (choose == 'q')
        {
            printf("Kahju, et lahkusite. Your finalscore: %d kulda ja level: %d\n", kuld, level);
            break;
        }
        else if (choose == 'i')
        {
            printf("You have %d potions right now.\n", inventar.potions);

            if (inventar.potions > 0)
            {
                printf("Do you want to drink a potion for +30 health?\n");
                printf("(y/n): ");
                scanf(" %c", &choose);
                if (choose == 'y' && health <= 70)
                {
                    health += 30;
                    inventar.potions--;
                }
                else if (choose == 'y' && health > 70)
                {
                    printf("You have over 70 hp, cant drink the potion right now!\n");
                }
            }
        }
        else if (choose == 'w')
            y++;
        else if (choose == 's')
            y--;
        else if (choose == 'a')
            x--;
        else if (choose == 'd')
            x++;

        // Juhuslik kohtumine
        if (rand() % 10 < 3)
        {
            // battle();
        }

        // shop at location x=2, y=2
        if (x == 2 && y == 2)
        {
            // shop();
        }
    }

    if (level == 5)
    {
        running = false;
        printf("Fantastic! You got all the treasures and escaped with %d gold!\n", kuld);
    }

    return 0;
}