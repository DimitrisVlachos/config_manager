# config_manager
A basic readable-text configuration manager

# Config Script Format 
variable_name = "data.here"

# Simple example :
    config_manager_c cfg("cfg.txt");
    std::cout << "value = " << cfg.gets("value") << std::endl;
    std::cout << "double value = " << cfg.getd("double") << std::endl;
     
    //Change value
    cfg.setd("double",7.0);
    
    //Update original
    cfg.update();
    
    //Or create new
    cfg.store("new.txt");
    
    
