#include "config.h"
#include "macros.h"



using namespace std;

//initialize functions
string get_config_path();
string change_file_path(string filePath);

int check_for_file(string filePath);
int create_file(string filePath);
int write_to_file(string filePath, string data);
void initialize_files();
void print_map();
void set_map_defaults();
void update_config_file(string filePath);
void change_file_name(string pathToFile, string prevName, string newName);

map<string,int> read_config(string filePath);


//initialize global variables
bool filePresent;
map <string,int> container;


/*
 * Class Constructor
 */
Config::Config()
{
    SHOW_WHERE;
    someData = 0;
    state = "Constructor";
    initialize_files();
    state = "Program running";
}

Config::Config(Config &obj)
{
  SHOW_WHERE;
  someData = obj.someData;
  state = "Constructor";
  initialize_files();
  state = "Program running";
}

void Config::operator =(Config &obj){someData = obj.someData;}

/*
 * Class Destructor
 */
Config::~Config(){
    state = "Destructor";
    //this method destroys the class Config
}


/*
 * Checks whether the configuration file
 * exists.
 * @param file_name : name of file being checked for
 * @return int : 1 if file is present, 0 if not
 */
int Config::check_for_file(string filePath){
    state = "File checking";
    ifstream myfile(filePath);
    if (myfile){
        filePresent = true;
        return 1;
    }
    filePresent = false;
    state = "Program running";
    return 0;
}

/*
 * Creates a configuration file if not already
 * present.
 * @param file_name : name of the file
 * @return int : returns 1 if the file was successfully
 * created, and 0 if file wasn't created
 */
int Config::create_file(string filePath){
    state = "Create file";
    int present = check_for_file(filePath);
    if (present != 1){
        ofstream file(filePath); //create file
        if(!file){ //check whether file was opened
            std::cout << "File could not be created\n";
            state = "Program running";
            return 0;
        }
        state = "Program running";
        return 1;
    } else {

        cout << "File" << filePath << "cannot be created : already exists\n";
    }
    state = "Program running";
    return 0;
}


/*
 * Changes the path to specified file to
 * the path input by user
 * @param prev_path : previous path to file
 * @return string : returns new string
 */
string Config::change_file_path(string prev_path){
    state = "Program running";
    string user = getenv("HOME");
    std::string new_path;

    std::cout << "Please enter your new path:\n";
    std::cin >> new_path;
    system(("mv " + prev_path + " " +new_path).c_str());
    write_to_file((user+"/preconfig.txt").c_str(),new_path);
    return new_path;

}

/*
 * Initializes the config file. It checks
 * whether the config file exists, and if not, one
 * is created.
 */
void Config::initialize_files(){

    state = "Configuration";
    string path;
    string user = getenv("HOME");

    // check for preconfig file
    if (!check_for_file((user + "/preconfig.txt").c_str())){
        cout << "Creating preconfig file...\n";
        create_file((user + "/preconfig.txt").c_str());
    }
    cout << "Preconfig file found...\n";

    // check for config file
    ifstream myfile((user + "/preconfig.txt").c_str());
    if (myfile){
        getline (myfile,path);
        myfile.close();
      }

    // create config file if there isn't
    if (path.empty()){
        cout << "Creating config file...\n";
        create_file((user + "/config.txt").c_str());
        change_file_path((user + "/config.txt").c_str());
        set_map_defaults();
    } else {
        cout << "Config file found..." << endl << endl;
        container = read_config(path);
    }
    update_config_file(path);
    state = "Program running";
}

/*
 * Writes a string of data to a file.
 * @param filePath : path to target file
 * @param data : string to be written to file
 * @return int : 1 if write is successful, 0 if not
 */
int Config::write_to_file(string filePath, string data){

    state = "Write file";
    ofstream myfile(filePath);
    if (myfile){
        myfile << data << "\n";
        myfile.close();
        state = "Program running";
        return 1;
    }
    cout << "Write failed : could not open file" << endl;
    state = "Program running";
    return 0;
}

/*
 * Reads data from the configuration
 * file and stores config data in a map container
 * @param filePath : path to target file
 * @return map<string,int> : returns map of file data
 */
map<string,int> Config::read_config(string filePath){

    state = "Read file";
    string line;
    string sub1;
    string sub2;
    string key;
    int value;
    ifstream myfile(filePath);
    map<string,int> cont;

    //read and store file data
    while (getline(myfile, line)){
            istringstream buffer(line);
            buffer >> sub1;
            buffer >> sub2;
            key = sub1;
            value = stoi(sub2);
            cont.insert (std::pair<string,int>(key,value));
    }
    state = "Program running";
    return cont;
}

/*
 * Changes the name of target file on a
 * specified path
 * @param path_to_file : path to target directory which
 * contains file
 * @param prev_name : name of target file
 * @param new_name : new name of file
 */
void Config::change_file_name(string pathToFile, string prevName, string newName){
    state = "Program running";
    system(("mv " + pathToFile+ "/" + prevName + " " + pathToFile+ "/" + newName).c_str());
}

/*
 * Updates the data in the config file
 * @param filePath : path to config file
 */
void Config::update_config_file(string filePath){

    state = "Write file";
    ofstream myFile(filePath);
    map<string,int>::iterator in;
        for(in=container.begin(); in!=container.end();in++){
                    string key = in->first;
                    int value = in->second;
                    myFile << key << " " << value << endl;
        }
        myFile.close();
        state = "Program running";
}

/*
 * Gets the path to the config file
 * @return string : returns path to config file
 */
string Config::get_config_path(){
    state = "Program running";
    string path;
    string err = "No configuration file";
    string user = getenv("HOME");
    if (!check_for_file((user + "/preconfig.txt").c_str())){
        cout << "Configuration file does not exist...\n";
        return err;
    }
    ifstream myfile((user + "/preconfig.txt").c_str());
    if (myfile){
        getline (myfile,path);
        myfile.close();
    } else {
      return err;
    }
    return path;
}

/*
 * Prints out the map in the configuration class
 */
void Config::print_map(){
    state = "Program running";
    typedef map <string,int>::iterator itr;
    cout << "Map size : " << container.size() << endl;
    cout << "Configuration parameters: " << endl;
    for (itr t=container.begin(); t!=container.end(); ++t){
        cout << "   " << t->first << " => " << t->second << '\n';
    }
    cout << endl;
}

void Config::set_map_defaults(){
    state = "Set defaults";
    string path = get_config_path();
    container.clear();
    container["empty"] = 0;

    update_config_file(path);

}

