// Mask for tress in window 1
int tree_mask[][2] = {
  {240,	265},
  {280,	295},
  {313,	321},
  {405,	591},
  {648,	759},
  {775,	790},
  {807,	818}, // Note this ends the first tree
  {1145,	1160},
  {1175,	1193},
  {1212,	1322},
  {1380,	1513},
  {1517,	1540},
  {1550,	1563},
  {1645,	1652},
  {1670,	1685},
  {1700,	1720}
};

// Mask for sign in window 2
int sign_mask[][2] = {
  {285,	324},
  {403,	442},
  {533,	571},
  {650,	688},
  {781,	819},
  {897,	935},
  {1028, 1067},
  {1143, 1181},
  {1275, 1313},
  {1389, 1428},
  {1523, 1559}
};

// Window panels - total number of leds, number of strips
const int panels[][2] = {
  {256, 5},
  {1833, 15},
  {1954, 15},
  {1163, 15},
  {1162, 14},
  {1248, 15},
  {0, 0},
  {744, 9},
  {0, 0}
};

// Window perimeters, for all but windows one and two are total
const int perimeters [][4] = {
  {100,	50,	100},
  {520, 102,	265, 363},
  {517, 104,	259, 360},
  {265,	70,	199},
  {269,	70,	200},
  {280,	70,	214},
  {230, 70, 160},
  {230, 71, 160},
  {250, 70, 175}
};

// Use the fuseID to return the correct window name
int windowNum (uint64_t var) {

  int thisNum;

  switch (var) {
  case 264390250713352:
    //thisName = "win0";
    thisNum = 0;
    break;
  case 202580436832520:
    //thisName = "win1";
    thisNum = 1;
    break;
  case 158785661948168:
    //thisName = "win2";
    thisNum = 2;
    break;
  case 278167046181128:
    //thisName = "win3";
    thisNum = 3;
    break;
  case 255446076935576:
    //thisName = "win4";
    thisNum = 4;
    break;
  case 198418596745480:
    //thisName = "win5";
    thisNum = 5;
    break;
  case 198512032212808:
    //thisName = "win6";
    thisNum = 6;
    break;
  case 158342005248264:
    //thisName = "win7";
    thisNum = 7;
    break;
  case 242038301380872:
    //thisName = "win8";
    thisNum = 8;
    break;
  
  default:
    thisNum = 99;
    break;
  }

  return thisNum;
}

