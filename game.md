Idee on tekstipõhine RPG. (tegevus toimub terminalis)

Sisaldus:
rooms,
character,
levels?,
mobs,
health,
items?;

Loogika:

Inimene spawnib siis room 0, kus tuleb siis algus tekst. Pärast seda saab valida kuhu liikuda, kasutades keyworde (a-west,w-north,d-east,s-south) samuti q to leave the game. Meelde jätmiseks ig on ka vaja siis alg väärtusi x ja y mis on alguses 0, north ja south tõstab siis y väärtust üles ja west, east tõstab x väärtust üles. Mõnel konkreetsel toal leiab siis kas vaenlase või mingi itemi, mis näiteks praegu healib elusid. Kui mobiga kohtud, siis dmg on random maybe ning on ka valik siis põgeneda. Leveli tõuseb näiteks koletise tapmise eest ning kui saad uue leveli siis teed rohkem dammi. SEE ON SIIS PRAEGU KÕIK, VAATAB KUI RASKEKS LÄHEB.

Funktsiooni näide:
void battle(int *player_hp) { //tähistab, et ootame aadressi
*player_hp -= 20; // Muudame väärtust sellel aadressil
}

int main(void) {
int hp = 100; // Kohalik muutuja
battle(&hp); // Saadame HP aadressi
printf("HP pärast võitlust: %d\n", hp); // Nüüd on 80!
return 0;
}
