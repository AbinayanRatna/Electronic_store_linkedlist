#include <iostream>

#include <fstream>

#include <sstream>

#include <string>

#include <string.h>

#include <algorithm>

using namespace std;

//structure for type of the items
struct nodeType {
  string typeName;
  struct nodeType * linkType;
  struct itemType * linkNextItem;
};

//structure for item
struct itemType {
  int value;
  string units;
  int noOfItems;
  float price;
  struct itemType * linkNextItem;
};

//typedef for structures
typedef struct nodeType * type;
typedef struct itemType * item;

type headType = new nodeType;
item headItem = new itemType;

//function for add new type
void userAddType(string typeNameUser) {

  type userTypeEntered = new nodeType; //creating a new node
  userTypeEntered -> typeName = typeNameUser; // making the name of the type as string inserted by user

  //finding whether the headtype node is null or not
  if (headType -> typeName == "") {
    headType = userTypeEntered;
    userTypeEntered -> linkType = NULL;
    userTypeEntered -> linkNextItem = NULL;
  } else {
    userTypeEntered -> linkType = headType;
    userTypeEntered -> linkNextItem = NULL;
    headType = userTypeEntered;
  }

  cout << "Type " << typeNameUser << " saved successfully." << endl << endl;
}

//function for add new item
int userAddItem(string itemTypeEnter, int value, string units, int noOfItems, float price) {
  type lastType = headType;

  bool isItemAdded = false;
  item lastItem = headItem;

  item newItem = new itemType;
  while (lastType != NULL) {
    if (lastType -> typeName == itemTypeEnter) {
      newItem -> value = value;
      newItem -> units = units;
      newItem -> noOfItems = noOfItems;
      newItem -> price = price;
      if (lastItem == NULL) {
        headItem = newItem;
        lastType -> linkNextItem = newItem;
        newItem -> linkNextItem = NULL;
      } else {
        headItem = lastType -> linkNextItem;
        newItem -> linkNextItem = headItem;
        headItem = newItem;
        lastType -> linkNextItem = newItem;
      }

      isItemAdded = true;
    }

    lastType = lastType -> linkType;

  }
  if (isItemAdded == true) {
    cout << "item saved successfully in the " << itemTypeEnter << " type." << endl << endl;
  } else {
    cout << "item not saved" << endl << endl;
  }
  return 0;
}

//function for search an item
int userSearchItem(string itemTypeEnter, int value, string units) {
  bool isItemAvailable = false;
  bool isTypeAvailable = false;

  type lastType = headType;
  item lastItem = headItem;
  while (lastType != NULL) {
    if (lastType -> typeName == itemTypeEnter) {
      lastItem = lastType -> linkNextItem;
      isTypeAvailable = true;
      while (lastItem != NULL) {
        if (lastItem -> value == value && lastItem -> units == units) {

          cout << lastType -> typeName << " : " << lastItem -> value << "  " << lastItem -> units << " - " << lastItem -> noOfItems << " - " << lastItem -> price << endl << endl;
          isItemAvailable = true;
          return 0;
        }

        lastItem = lastItem -> linkNextItem;

      }
    }

    lastType = lastType -> linkType;

  }
  if (isItemAvailable == false) {
    cout << "item not available in the type ." << endl << endl;
  }
  if (isTypeAvailable == false) {
    cout << "type not available ." << endl << endl;
  }
  return 0;
}

//function for delete an item
int userDeleteItem(string itemTypeEnter, int value, string units) {
  type lastType = headType;
  item nextItem = new itemType;
  item lastItem = headItem;
  item previousItem = headItem;
  item temp = headItem;
  item prev = new itemType;

  while (lastType != NULL) {
    if (lastType -> typeName == itemTypeEnter) {
      lastItem = lastType -> linkNextItem;
      while (lastItem != NULL) {
        if (lastItem -> value == value && lastItem -> units == units) {
          if (lastType -> linkNextItem == lastItem) {
            headItem = lastItem -> linkNextItem;
            delete lastItem;
            lastType -> linkNextItem = headItem;
            cout << "deleted successfully" << endl << endl;
            return 0;

          } else if (lastItem -> linkNextItem == NULL) {
            lastItem = headItem;
            while (lastItem -> linkNextItem != NULL) {
              prev = lastItem;
              lastItem = lastItem -> linkNextItem;
            }
            prev -> linkNextItem = NULL;
            delete lastItem;
            cout << "deleted successfully" << endl << endl;
            return 0;
          } else {
            nextItem = lastItem -> linkNextItem;
            lastItem -> value = nextItem -> value;
            lastItem -> units = nextItem -> units;
            lastItem -> noOfItems = nextItem -> noOfItems;
            lastItem -> price = nextItem -> price;
            lastItem -> linkNextItem = nextItem -> linkNextItem;
            delete nextItem;
            cout << "deleted successfully" << endl << endl;
            return 0;
          }

        }
        lastItem = lastItem -> linkNextItem;
      }
      return 0;

      return 0;
    }

    lastType = lastType -> linkType;

  }
  return 0;

}

//function for sell an item
int userSellItem(string itemTypeEnter, int value, string units, int valueSell) {

  bool isItemAvailable = false;
  int noOfItems;
  int amountOfItems;
  type lastType = headType;
  item lastItem = headItem;

  while (lastType != NULL) {
    if (lastType -> typeName == itemTypeEnter) {
      lastItem = lastType -> linkNextItem;

      while (lastItem != NULL) {
        if (lastItem -> value == value && lastItem -> units == units) {
          amountOfItems = lastItem -> noOfItems;
          if (valueSell < amountOfItems) {
            noOfItems = amountOfItems - valueSell;
            lastItem -> noOfItems = noOfItems;
            cout << "item sold successfully." << endl << endl;

            return 0;
          } else {
            cout << "selling amount of items is higher than the available amount" << endl;
          }
        }

        lastItem = lastItem -> linkNextItem;

      }
      return 0;
    }

    lastType = lastType -> linkType;

  }
  if (isItemAvailable == false) {
    cout << "item not available" << endl << endl;
  }

  return 0;
}

//function for buy an item
int userBuyItem(string itemTypeEnter, int value, string units, int valueBuy) {

  bool isItemAvailable = false;
  int noOfItems;
  int amountOfItems;
  type lastType = headType;
  item lastItem = headItem;

  while (lastType != NULL) {
    if (lastType -> typeName == itemTypeEnter) {
      lastItem = lastType -> linkNextItem;

      while (lastItem != NULL) {
        if (lastItem -> value == value && lastItem -> units == units) {
          amountOfItems = lastItem -> noOfItems;
          noOfItems = amountOfItems + valueBuy;
          lastItem -> noOfItems = noOfItems;
          cout << lastType -> typeName << " : " << lastItem -> value << "  " << lastItem -> units << " - " << lastItem -> noOfItems << " - " << lastItem -> price << endl << endl;
          isItemAvailable = true;
          return 0;
        }

        lastItem = lastItem -> linkNextItem;

      }
      return 0;
    }

    lastType = lastType -> linkType;

  }
  return 0;

  if (isItemAvailable == false) {
    cout << "item not available" << endl << endl;
  }
  return 0;
}

//function for set new price for an item
int usersetNewPrice(string itemTypeEnter, int value, string units, float newPrice) {
  bool isItemAvailable = false;
  int noOfItems;
  float oldPrice;
  type lastType = headType;
  item lastItem = headItem;

  while (lastType != NULL) {
    if (lastType -> typeName == itemTypeEnter) {
      lastItem = lastType -> linkNextItem;
      while (lastItem != NULL) {
        if (lastItem -> value == value && lastItem -> units == units) {
          lastItem -> price = newPrice;
          cout << lastType -> typeName << " : " << lastItem -> value << " " << lastItem -> units << " - " << lastItem -> noOfItems << " - " << lastItem -> price << endl << endl;
          isItemAvailable = true;
          return 0;
        }

        lastItem = lastItem -> linkNextItem;

      }
      return 0;
    }

    lastType = lastType -> linkType;

  }
  return 0;
  if (isItemAvailable == false) {
    cout << "item not available" << endl << endl;
  }
  return 0;
}

//function for sorting the items
int userSortItem(string type_name) {
  type type_list = headType;

  type current_type = type_list;
  while (current_type != NULL && current_type -> typeName != type_name) {
    current_type = current_type -> linkType;
  }

  if (current_type == NULL) {

    cout << "Type entered is not found !!" << endl;
    return 0;
  }

  item current_item = current_type -> linkNextItem;
  item a = new itemType;
  item b = new itemType;
  float temporary;
  string unitsTemp;
  float noOfItemsTemp;
  float priceTemp;

  for (a = current_item; a -> linkNextItem != NULL; a = a -> linkNextItem) {
    for (b = a -> linkNextItem; b != NULL; b = b -> linkNextItem) {
      if (a -> value > b -> value) {
        temporary = a -> value;
        unitsTemp = a -> units;
        noOfItemsTemp = a -> noOfItems;
        priceTemp = a -> price;
        a -> value = b -> value;
        a -> units = b -> units;
        a -> noOfItems = b -> noOfItems;
        a -> price = b -> price;
        b -> value = temporary;
        b -> units = unitsTemp;
        b -> noOfItems = noOfItemsTemp;
        b -> price = priceTemp;

      }
    }
  }
  cout << "Sorted in ascending order" << endl << endl;
  return 0;
}

//function for display the same type items
int userDisplayItem(string itemTypeEnter) {
  bool isItemAvailable = false;
  bool isItemDeleted = false;
  int value;
  string units;
  type lastType = headType;
  item lastItem = headItem;

  while (lastType != NULL) {
    if (lastType -> typeName == itemTypeEnter) {

      lastItem = lastType -> linkNextItem;

      while (lastItem != NULL) {

        cout << lastItem -> value << " " << lastItem -> units << " " << lastItem -> noOfItems << " - " << lastItem -> price << endl;

        lastItem = lastItem -> linkNextItem;

      }
      cout << "Items are displayed" << endl << endl;
    }

    lastType = lastType -> linkType;

  }
  return 0;

  return 0;
}

int main(int argv, char * argc[]) {
  //Declare variables
  fstream File; //Create File Object to read the file
  string fileLine; //String variable to hold a line of text from the file
  //check whether there are any input parameters to the programme
  //when it is launched

  if (argv < 1) {
    //no arguments other than the programme name is provided
    //so, no file name is provided as parameter to the program
    cerr << "Error: No input file name is provided" << endl;
    return -1;
  }
  //open the file
  File.open("inputs.txt", ios::in); //file name and file stream type
  //print the content to the console
  while (getline(File, fileLine)) {
    //to get commands as a input from file
    string sentence;
    sentence = fileLine;
    istringstream ss(sentence);
    string typeWord;
    int word_2,word_4;
    float word_5;
    string word_1, word_3,word_6;

    ss >> word_1 >> typeWord >> word_2 >> word_3 >> word_4 >> word_5 >> word_6;

    if (word_1 == "CREATE") {
      userAddType(typeWord);
    } else if (word_1 == "ADD") {
      userAddItem(typeWord, word_2, word_3, word_4, word_5);
    } else if (word_1 == "SEARCH") {
      userSearchItem(typeWord, word_2, word_3);
    } else if (word_1 == "DELETE") {
      userDeleteItem(typeWord, word_2, word_3);
    } else if (word_1 == "SELL") {
      userSellItem(typeWord, word_2, word_3, word_4);
    } else if (word_1 == "BUY") {
      userBuyItem(typeWord, word_2, word_3, word_4);
    } else if (word_1 == "SETPRICE") {
      usersetNewPrice(typeWord, word_2, word_3, word_4);
    } else if (word_1 == "SORT") {
      userSortItem(typeWord);
    } else if (word_1 == "DISPLAY") {
      userDisplayItem(typeWord);
    } else if (word_1 == "EXIT") {
      return 0;
    } else {
      cout << "No valid input.Try again !!";
      return 0;
    }

  }
  //close the file
  File.close();
  return 0;
}
