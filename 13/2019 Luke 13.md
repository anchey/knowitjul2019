# The A-maze-ing Race

Av: Sverre Johann Bjørke

Til jul har Arthur og Isaac fått kvar sin robot som kan programmerast til å løyse labyrintar. Dei programerar inn to ganske like strategiar, og set robotane til å løyse [denne labyrinten (zippet)](https://julekalender.knowit.no/resources/2019-luke13/maze.txt.zip) på 500x500 rom. Begge startar i rom `(0,0)` (nordvestre hjørne), og målet er i rom `(499, 499)` (sydaustre hjørne).

Arthur har følgande strategi:

* Roboten prioriterar alltid ubesøkte rom før besøkte.
* Roboten prioriterar ubesøkte rom i denne rekkefølga: `syd, aust, vest, nord`.
* Om det er ingen ubesøkte rom å gå til, går roboten tilbake til forrige rom.

Isaac programerar sin identisk, bortsett frå at roboten hans prioriterar å besøke nye rom i rekkefølga `aust, syd, vest, nord`

Eit enkelt rom i labyrinten har følgande eigenskapar:
* x - x-posisjon i labyrinten
* y - y-posisjon i labyrinten
* nord - `true` om romet er stengt av ein vegg i retning nord. `false` om det er passasje til tilstøytande rom.
* vest -  `true` om romet er stengt av ein vegg i retning vest. `false` om det er passasje til tilstøytande rom.
* syd - `true` om romet er stengt av ein vegg i retning syd. `false` om det er passasje til tilstøytande rom.
* aust - `true` om romet er stengt av ein vegg i retning aust. `false` om det er passasje til tilstøytande rom.


## Spørsmål
Kor mange *færre* rom besøkte vinnarroboten? Gjentekne besøk til eit rom som er besøkt før skal ikkje tellast.
