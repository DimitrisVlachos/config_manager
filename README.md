# config_manager
A basic readable-text configuration manager

# Config Script Format 
variable_name = "data.here"

array_variable_name = "0.0,1.0,2.0,3.0,4.0"

# Simple example :

#include "config_mgr.hpp"

int main() {
    config_manager_c cfg("cfg.txt");
    std::cout << "value = " << cfg.gets("value") << std::endl;
    std::cout << "double value = " << cfg.getd("double") << std::endl;
     
    //Change value
    cfg.setd("double",7.0);
    
    //Read vector
    std::vector<double> my_doubles;
    cfg.getd("array_variable_name",my_doubles,",;"); //delimiter list
    
    //Update original
    cfg.update();
    
    //Or create new
    cfg.store("new.txt");
    return 0;
}
    
    
