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
int gainXp = 0;
int remainingxp = 100;

typedef struct
{
    int shopPotions;
    int treasurePotions;
} Inventar;

Inventar inventar = {
    .shopPotions = 0,
    .treasurePotions = 1,
};

void inventaar(void);
void fear(void);
void battle(int monsterLVL);

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
        bool movedThisTurn = false;

        if (choose == 'w')
        {
            y++;
            movedThisTurn = true;
        }
        else if (choose == 's')
        {
            y--;
            movedThisTurn = true;
        }
        else if (choose == 'a')
        {
            x--;
            movedThisTurn = true;
        }
        else if (choose == 'd')
        {
            x++;
            movedThisTurn = true;
        }

        // Juhuslik kohtumine
        if (movedThisTurn && rand() % 10 < 3)
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

void inventaar(void)
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
    int monsterLevel = rand() % 5;
    char monsterChoice;
    printf("\nPimedast ilmub välja level %d metslik koll! Your feet are shaking...\n", monsterLevel);
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
        battle(monsterLevel);
        break;
    case 'e':
        printf("You escaped from the monster!\n");
    }
}

void battle(int monsterLVL)
{
    int damage = 0;
    int monsterDamage = 0;
    int currentMonsterHP = monsterHP + (10 * monsterLVL * 0.8);
    int multiplierPercent = 100 + 10 * (level - 1);
    int monsterMultiplierPercent = 100 + 10 * monsterLVL;
    while (health > 0 && currentMonsterHP > 0)
    {

        char action;
        printf("\n Your HP: %d | Monster HP: %d\n", health, currentMonsterHP);
        printf("(a=attack, p=potion, r=run): ");
        scanf(" %c", &action);

        if (action == 'a')
        {
            damage = (rand() % 11) + 5;
            float scaledDamage = damage * (multiplierPercent / 100.0f);
            currentMonsterHP -= scaledDamage;
            if (currentMonsterHP <= 0)
            {
                kuld += (rand() % 10) + 5;
                gainXp = (rand() % 30) + 10;
                remainingxp = remainingxp - gainXp;
                if (remainingxp <= 0)
                {
                    level++;
                    remainingxp = 100;
                    printf("Congratulations you leveled up! You are level %d now!\n", level);
                }
                printf("Congratulations! You killed the monster and got %d gold + %d xp\n", kuld, gainXp);
                printf("%d xp remaining until next level!\n", remainingxp);
                break;
            }
            printf("You did %.2f damage to the monster! Monster has %d health remaining\n", scaledDamage, currentMonsterHP);

            monsterDamage = (rand() % 11);
            float monsterScaledDamage = monsterDamage * (monsterMultiplierPercent / 100.0f);
            health -= monsterScaledDamage;
            if (health <= 0)
            {
                printf("You failed to escape the dungeon!\n");
                running = false;
                break;
            }
            printf("The monster attacked you for %.2f damage! You have %d health remainig\n", monsterScaledDamage, health);
        }
        else if (action == 'p')
        {
            inventaar();
        }
        else if (action == 'r')
        {
            if (rand() % 100 < 50)
            {
                monsterDamage = (rand() % 11);
                float monsterScaledDamage = monsterDamage * (monsterMultiplierPercent / 100.0f);
                health -= monsterScaledDamage;
                printf("You failed to escape!\n");
                printf("The monster attacked you for %.2f damage! You have %d health remainig\n", monsterScaledDamage, health);
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("Vale valik.\n");
            continue;
        }
    }
}