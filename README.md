# a_curtain include for San Andreas Multiplayer (SA:MP)

| file name | Latest release | Version | WIKI | Collaborators |
| :---: | :---: | :---: | :---: | :---: |
| a_extensions | [check](https://github.com/pnb-pontes/-SAMP-Include-extension/releases/tag/(a_extensions)-v1.19.41.0) | v1.19.41.0 | [wiki](-) | - |

-------------------------------------------------

**This include is a compilation of all my codes for the community.**

**Functions provided**
-----------------------------------

##### 🎪 CURTAIN

 - ShowPlayerCurtain `show the curtain`
 - HidePlayerCurtain `destroy the screen curtain`
 - IsCurtainExist `checks if the player has a curtain being shown`

#### 📁 FILE

 - fcreate `create a file`
 - frename `rename a file`
 - fcopy `copy a file`
 - fbackup `creates a backup of the file`
 - fclear `clears properties inside the file`

 - fgetlines `gets the number of lines the file has`
 - fkeyexist `checks if a key exists`
 - fkeyrename `rename a key`
 - fkeyremove `remove a key`

 - fsetstring `sets a string to a file`
 - fgetstring `get the string from a file`

 - fsetkeystring `sets a string from a Key in an file`
 - fsetkeyinteger `sets a integer from a Key in an file`
 - fsetkeyfloating `sets a floating from a Key in an file`
 - fsetkeyboolean `sets a boolean from a Key in an file`

 - fgetkeystringex `stores the string of a key in a file in a variable`

 - fgetkeystring `gets a string from a Key in an file`
 - fgetkeyinteger `gets a integer from a Key in an file`
 - fgetkeyfloating `gets a floating from a Key in an file`
 - fgetkeyboolean `gets a boolean from a Key in an file`

#### 📷 CAMERA FIRST PERSON

 - ResetCamPosFirstPersonPlayer `returns all camera positions of a player to default`
 - SetCamPositionFirstPersonPlayer `changes a player's camera position`
 - SetCamFirstPersonPlayer `Sets the player's camera to first person`
 - CancelCamFirstPersonPlayer `cancel the first person camera`
 - IsCamFirstPersonPlayer `check if the camera is set to first person`

#### 📚 MATHEMATICS 

- MathRandomEx `pick a random number, whether positive or negative`
- MathPow `takes the power of a number over its exponent`
- MathSqRoot `get the integer square root of a number`
- MathSqRootRest `get the remainder of the square root of a number`
  
#### 👔 SKIN

 - IsValidSkinID `check for skin`
 - GetSkinName `takes the name of a skin`
 - GetSkinModelName `takes the model name of a skin`
 - GetSkinSex `get the skin genre`
 - GetSkinSexName `get the skin genre name`
 - GetSkinLocal `returns the location where the npc(skin) is found`
 - GetSkinLocalName `takes the name of the location`

-----------------------------------

**Callbacks provided**
-----------------------------------

#### 🎪 CURTAIN
- OnPlayerUpdateCurtain `performed as the curtain is closed`
- OnPlayerCurtainClosed `performed while curtain closes completely`

-----------------------------------
