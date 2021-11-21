Saves all your Valheim worlds and characters to quickly restore them.

Since Valheim doesn't really provide the possibility to save/load games I decided to build a little application for it. Just start the application and click on save to store all your Valheim worlds and characters in another folder. You can then select one of the saved games in the application and restore them quickly with "Load". Before you save your game you **have to** log out of the world first, since that is the only way to save both the world and the character. Before loading a new world you also have to log out of the world first and after pressing "Load" in the application you can log back in.

### Todo
- [ ] Allow user to change the game path and change where the saved states are stored.
- [ ] Implement system wide hotkeys to enable users to save/load without tabbing out of the game.
- [ ] Find out what the Valheim files do each and only store the relevant ones (`.db.old` for example).
