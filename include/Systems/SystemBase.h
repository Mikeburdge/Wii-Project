#ifndef SYSTEMBASE_H_
#define SYSTEMBASE_H_

class SystemBase
{
public:
    /**
     * Default Constructor
     * @brief Creates SystemBase With Default Variables
    */
    SystemBase();
    
    /**
     * @brief SystemBase will provide a virtual deconstructor to its children to deconstruct variables
    */
    virtual ~SystemBase(); 

    /**
    * Initialize
    *     * Use for setting variables when the system is first set up
    */
    virtual void Init() = 0;
    
    /**
    * Update
    * Each system will need to update themselves
    * @param DeltaTime Deltatime is the calculation of the time since the previous frame and the current frame 
    */
   virtual void Update(float DeltaTime) = 0;

};

#endif /*SYSTEMBASE_H_*/