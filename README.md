Harry Polis, Hermione Grannopark, Ron Weasinno and others from Hogwartolis applied to Innopolis University and got accepted, and when they reached Innopolis they saw people coding and doing things that are similar to magic like solving assignments and exercises from ITP course. So, they decided to teach the students magic and then they created their own club for magic. However, friends were unable to choose the club head and decided to ask other students for assistance. For this students created teams and each team chose their unique favorite magician. The teams decided to compete between each other by playing a duel with multiple teams playing simultaneously. The winning team's choice of the club head should become the solution for the game. Help students to play the game by using mysterious C code. Let the magic begin!

In the <sub>input.txt</sub> file you will have the following content separated by a new line:
<ol>
<li>The number <b>N</b> (<b>1</b> ≤ <b>N</b> ≤ <b>10</b>), which is the number of teams in the game.</li>
<li><b>N</b>  lines, each line should contain a unique magician name with length <b>L</b> (<b>2</b> ≤ <b>L</b> ≤ <b>20</b>) made of only English letters and should begin with capital letter. Each of those magician names should correspond to the team number from <b>0</b> till <b>N-1</b>, which was chosen by this team to become the head of the club.</li>
<li>The number of the players <b>M</b> (<b>N</b> ≤ <b>M</b>≤ <b>100</b>). After this you will have <b>M*4</b> lines, each line will represent a player <i>i</i> information:
 <ul><li>The unique name of the player namei with length <b>L</b> (<b>2</b> ≤ <b>L</b> ≤ <b>20</b>) should contain only English letters and begin with capital letter.</li>
  <li>Team number for this player <i>t_i</i> (<b>0</b> ≤ <i>t_i</i> < <b>N</b>).</li>
  <li>The power of the player <i>p_i</i> (<b>0</b> ≤ <i>p_i</i> ≤ <b>1000</b>), which is integer value.</li>
  <li>The visibility of the player <i>v_i</i> (<i>True</i>/<i>False</i>).</li>
 </ul>
 </li>
 <li>Sequence of actions for players <b>S</b> (<b>0</b> ≤ <b>S</b> ≤ <b>1000</b>) followed on the same line by 1 or 2 player names separated by single spaces. Not each player is guaranteed to have actions. Next actions are applicable:
 <ul>
  <li><i>attack name_i name_j</i><ul>
   <li>if <i>p_i</i> > <i>p_j</i>, then <i>player_i</i> will gain <i>p_i</i> − <i>p_j</i> power and <i>player_j</i> will have no power left and further will be called <b>frozen</b>.</li>
   <li>if <i>p_i</i> < <i>p_i</i>, then <i>player_i</i> will be frozen and <i>player_j</i> will gain <i>p_j</i> − <i>p_i</i> <b>power</b>.</li>
    <li> if <i>player_j</i> is not <b>visible</b>, then the *player_i* will be <b>frozen</b>.</li>
   <li>if <i>p_i</i> = <i>p_j</i>, then both players will be <b>frozen</b>.</li>
   </ul></li>
  <li><i>flip_visibility name_i</i> will flip the status of the <b>visibility</b> of the <i>player_i</i>.</li>
  <li><i>heal name_i name_j</i> will make <i>player_i</i> give half (ceil the numbers up for both players if needed) of his power to <i>player_j</i> (from the same team).</li>
  <li><i>super name_i name_j</i> will create a super player instead of existing <i>2</i> players (from the same team) with joint power and actions. The power will be <i>p_i</i>+<i>p_j</i> (sum at most <b>1000</b>, a greater sum should be floored down to <b>1000</b>) and the visibility will be <i>True</i> and the name assigned to super player will be <i>S_k</i>, where <i>k</i> is the index of super player (<i>k</i> begins with <i>0</i> and increments for each next new created super player).</li>
  </ul>
 </li>
</ol>

A frozen player can be <i>healed</i>, then this player will be <i>unfrozen</i>. A player with <i>visibility</i> equal to <i>False</i> can be <i>healed</i>. A frozen <i>player_j</i> can be in the action in <i>super name_i name_j</i>. A playerj with <i>visibility</i> equal to <i>False</i> can be in the action in <i>super name_i name_j</i>.

You might have a team with zero players, but it is guaranteed that all players have assigned teams.

The cases when you cannot perform the actions, but they should not stop the game and the actions should be ignored:
<ol>
 <li>If a player with the <i>visibility</i> equal to <i>False</i> tries to make any action other than <i>flip_visibility</i>, then the next warning message should be added to the output file: "<i>This player can't play</i>".</li>
 <li>If a <i>frozen</i> player tries to make an action, then the next warning message should be added to the output file: "<i>This player is frozen</i>".</li>
 <li>In case of <i>heal</i> or <i>super</i> action, if players are from different teams, then the next warning message should be added to the output file: "<i>Both players should be from the same team</i>".</li>
 <li>The player shouldn't be able to <i>heal</i> itself, in this case in the output file the next warning message should be added: "<i>The player cannot heal itself</i>".</li>
 <li>If during creation of a <i>super</i> player the <i>player_i</i> unites with <i>player_i</i>, then the next warning message should be added to the output file: "<i>The player cannot do super action with itself</i>".</li>
</ol>
<b>If multiple described errors happen for a single action, print ONLY the first one of them in the order given above.</b>

The input file has to be read until the end and all actions have to be performed sequentially.

At the end of the output file the next message should be added: "<i>The chosen wizard is #team's_wizard</i>" (the wizard of the team which has the greatest power left which is the sum of all the team members' powers). If more than 1 team has the greatest power the output file should contain a different message, which is: "<i>It's a tie</i>".

The <i>input.txt</i> file may contain invalid inputs, which has to be detected and reported in the <i>output.txt</i> file with the only error message "<i>Invalid inputs</i>". If the output file already contains some other previous messages, everything has to be replaced by an error message.

P.S.: It is guaranteed that magicians' and players' names are not intersecting in the same test, i.e. you should not expect the input with the player and magician having the same name.

P.P.S.: You have to use structure(s) for this assignment

<h3>Examples:</h3>

<h5>input</h5>
```
5
Harry
Hermione
Ron
Draco
Ginny
5
Munir
0
1000
True
Alaa
1
500
True
Mohamad
2
650
True
Alexandr
3
800
True
Mikhail
4
900
True
flip_visibility Alaa
attack Mohamad Alexandr
attack Munir Mikhail
attack Munir Alexandr
attack Munir Alaa
```
<h5>output</h5>
```
The chosen wizard is Hermione
```
<h5>input</h5>
```
4
Harry
Hermione
Ron
Draco
8
Gary
0
800
True
Ronald
0
650
False
Sybill
1
350
True
Padma
1
900
True
Hengist
2
190
False
Bridget
2
589
True
Darco
3
950
True
MARCUS
3
469
True
attack Gary MARCUS
attack Darco Ronald
attack Darco Bridget
flip_visibility Bridget
attack Padma Gary
```
<h5>output</h5>
```
This player is frozen
The chosen wizard is Harry
```
<h5>input</h5>
```
5
Harry
Hermione
Ron
Draco
Ginny
5
Munir
0
1000
True
Alaa
1
500
True
Mohamad
2
650
True
Alexandr
3
800
True
Mikhail
4
900
True
flip_visibility Alaa
attack Mohamad Alexandr
attack Munir Mikhail
attack Alaa Munir
attack Mikhail Munir
super Mikhail Alaa
attack Munir Alexandr
attack Munir Alaa
heal Munir Alaa
```
<h5>output</h5>
```
This player can't play
This player is frozen
This player is frozen
This player is frozen
The chosen wizard is Hermione
```
<h5>input</h5>
```
5
Harry
Hermione
Ron
Draco
Ginny
5
Munir
0
1000
True
Alaa
1
1000
True
Mohamad
2
650
True
Alexandr
3
800
True
Mikhail
4
900
True
attack Mohamad Alexandr
attack Munir Mikhail
attack Munir Alexandr
attack Munir Alaa
```
<h5>output</h5>
```
It's a tie
```
<h5>input</h5>
```
5
harry
Hermione
Ron
Draco
Ginny
5
Munir
0
1000
True
Alaa
1
1000
True
Mohamad
2
650
True
Alexandr
3
800
True
Mikhail
4
900
True
attack Mohamad Alexandr
attack Munir Mikhail
attack Munir Alexandr
attack Munir Alaa
```
<h5>output</h5>
```
Invalid inputs
```
<h5>input</h5>
```
2
Harry
Hermione
5
Munir
0
1000
True
Alaa
1
499
True
Mohamad
1
650
True
Alexandr
1
250
True
Mikhail
1
250
True
attack Munir Mohamad
heal Munir Mohamad
heal Alaa Mohamad
super Alaa Mohamad
super S_0 Alexandr
super S_1 Mikhail
attack Munir S_2
```
<h5>output</h5>
```
Both players should be from the same team
It's a tie
```
<h5>input</h5>
```
3
Harry
Hermione
Darko
5
Munir
0
1000
True
Alaa
1
499
True
Mohamad
1
650
True
Alexandr
1
250
True
Mikhail
2
0
False
attack Munir Mohamad
heal Munir Mohamad
heal Alaa Mohamad
super Alaa Mohamad
super S_0 Alexandr
attack Munir S_1
super Mikhail Munir
```
<h5>output</h5>
```
Both players should be from the same team
This player can't play
The chosen wizard is Harry
```
