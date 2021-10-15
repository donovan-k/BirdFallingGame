# Sky Diving Game

## Description

This game is 2D skydiving game where a person goes across the screen and falls when the down arrow or space is pressed. The goal of the game is to pass all 10 rounds. To pass each round you must get a score of at least 100. Hitting the red target at the bottom gives you 100 points and hitting birds in the sky give you 10 points each hit. The lighter areas have wind. Wind moves the player in a random velocity that changes each fall. Each round comes with a chance of rain which makes you fall faster. Since it is a chance of rain the earlier rounds are less likely to rain, but the later rounds have a higher chance and produce more rain. The leaderboard to the side keeps track of the scores of recent falls.

### Photos

![](https://user-images.githubusercontent.com/48697778/117327107-df7f9400-ae57-11eb-8dec-efc949253ccb.png)
![](https://user-images.githubusercontent.com/48697778/117327374-24a3c600-ae58-11eb-8dc4-885c1e89f96b.png)

### Plays

![](https://user-images.githubusercontent.com/48697778/117330812-b06b2180-ae5b-11eb-9772-370877e21b00.gif)

## To Set Up and Run the Game

> To run the game, the prefered method is using CLion by jetbrains using Visual Studio 2015 for building. You could also just use Visual Studio 2015 to run the project as well. You will need an api called Cinder to run this game. To set up Cinder for CLion follow https://courses.grainger.illinois.edu/cs126/sp2021/notes/cinder-installation-notes/. After you have Cinder all set up, place this game directory into the folder called my-projects and it should let you run it. To run it look in the top right corner for the hammer and to the right of it should be configurations and you can drop down to select skydiving-game and then click the play button to run. Another way to run it is to go to the app folder and double click onto cinder_project_main.cc and in the file you should see a play button on the side to run it. 

## Controls

### Keyboard

| Key           | Action                              |
| ------------- | ------------------------------------|
| `space`       | Makes player start falling          |
| `down arrow`  | Same as space                       |
| `left arrow`  | Decreases the players x velocity    |
| `right arrow` | Increases the players x velocity    |
| `backspace`   | Resets player to starting position  |
