Harry Polis, Hermione Grannopark, Ron Weasinno and others from Hogwartolis applied to Innopolis University and got accepted, and when they reached Innopolis they saw people coding and doing things that are similar to magic like solving assignments and exercises from ITP course. So, they decided to teach the students magic and then they created their own club for magic. However, friends were unable to choose the club head and decided to ask other students for assistance. For this students created teams and each team chose their unique favorite magician. The teams decided to compete between each other by playing a duel with multiple teams playing simultaneously. The winning team's choice of the club head should become the solution for the game. Help students to play the game by using mysterious C code. Let the magic begin!

In the <sub>input.txt</sub> file you will have the following content separated by a new line:
<ol>
<li>The number <b>N</b> (<b>1</b> ≤ <b>N</b> ≤ *<b>10</b>), which is the number of teams in the game.</li>
<li><b>N</b>  lines, each line should contain a unique magician name with length **L** (<b>2</b> ≤ <b>L</b> ≤ <b>20</b>) made of only English letters and should begin with capital letter. Each of those magician names should correspond to the team number from <b>0</b> till <b>N-1</b>, which was chosen by this team to become the head of the club.</li>
<li>The number of the players <b>M</b> (<b>N</b> ≤ <b>M</b>≤ <b>100</b>). After this you will have <b>M*4</b> lines, each line will represent a player *i* information:
 <ul><li>The unique name of the player namei with length <b>L</b> (<b>2</b> ≤ <b>L</b> ≤ <b>20</b>) should contain only English letters and begin with capital letter.</li>
  <li>Team number for this player *t_i* (<b>0</b> ≤ *t_i* < <b>N</b>).</li>
  <li>The power of the player *p_i* (<b>0</b> ≤ *p_i* ≤ <b>1000</b>), which is integer value.</li>
  <li>The visibility of the player *v_i* (*True*/*False*).</li>
 </ul>
 </li>
 <li>Sequence of actions for players <b>S</b> (<b>0</b> ≤ <b>S</b> ≤ <b>1000</b>) followed on the same line by 1 or 2 player names separated by single spaces. Not each player is guaranteed to have actions. Next actions are applicable:
 <ul>
  <li>*attack name_i name_j*<ul>
   <li>if *p_i* > *p_j*, then *player_i* will gain *p_i−p_j* power and *player_j* will have no power left and further will be called <b>frozen</b>.</li>
   <li>if *p_i* < *p_j*, then *player_i* will be frozen and *player_j* will gain *p_j−p_i* <b>power</b>.</li>
    <li> if *player_j* is not **visible**, then the *player_i* will be <b>frozen</b>.</li>
   <li>if *p_i* = *p_j*, then both players will be **frozen**.</li>
   </ul></li>
  <li>*flip_visibility name_i* will flip the status of the <b>visibility</b> of the *player_i*.</li>
  </ul>
 </li>
</ol>
