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
    int shopPotions;
    int treasurePotions;
} Inventar;

Inventar inventar = {
    .shopPotions = 0,
    .treasurePotions = 1,
};

int inventaar(void);
void fear(void);

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
            inventaar();
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
            fear();
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

int inventaar(void)
{
    char invChoice;
    printf("You have %d shopPotions right now.\n", inventar.shopPotions);
    printf("You have %d treasurePotions right now.\n", inventar.treasurePotions);

    if (inventar.shopPotions > 0)
    {
        printf("Do you want to drink a potion for +30 health?\n");
        printf("(y/n): ");
        scanf(" %c", &invChoice);
        if (invChoice == 'y' && health <= 70)
        {
            health += 30;
            inventar.shopPotions--;
        }
        else if (invChoice == 'y' && health > 70)
        {
            printf("You have over 70 hp, cant drink the potion right now!\n");
        }
    }

    if (inventar.treasurePotions > 0)
    {
        printf("Do you want to drink a potion for +15 health?\n");
        printf("(y/n): ");
        scanf(" %c", &invChoice);
        if (invChoice == 'y' && health <= 85)
        {
            health += 15;
            inventar.treasurePotions--;
        }
        else if (invChoice == 'y' && health > 85)
        {
            printf("You have over 85 hp, cant drink the potion right now!\n");
        }
    }
}

void fear(void)
{
    char monsterChoice;
    printf("\nPimedast ilmub välja metslik koll! Your feet are shaking...\n");
    do
    {
        printf("Will you fight or run?(f=fight/e=escape): ");
        scanf(" %c", &monsterChoice);

        if (monsterChoice != 'f' && monsterChoice != 'e')
        {
            printf("Wrong choice! Choose f or e\n");
        }
    } while (monsterChoice != 'f' && monsterChoice != 'e');

    switch (monsterChoice)
    {
    case 'f':
        // battle();
        break;
    case 'e':
        printf("You escaped from the monster!\n");
    }
}