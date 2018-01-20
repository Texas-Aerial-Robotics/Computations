#include <gazebo/gazebo.hh>
#include <ignition/math.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>



namespace gazebo
{
  class target5 : public ModelPlugin
  {
  	public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
  	{
 
  
  		this->model = _parent;
  		
  			//animation
  			gazebo::common::PoseAnimationPtr anim(
  				//name animation
  				// set time
  				// put on loop
  				new gazebo::common::PoseAnimation("test",40.0,true));



				gazebo::common::PoseKeyFrame *key; //no idea what this line does lol
  		
		// this needs to be modeled correctly	
  		//set starting location of roombah
  		key = anim->CreateKeyFrame(0);
        	key->Translation(ignition::math::Vector3d(-.309,.951, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
        	
        	// set waypoint location after 2 seconds
        	key = anim->CreateKeyFrame(6.0);
        	key->Translation(ignition::math::Vector3d(-.927,2.853,0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
        	
        	key = anim->CreateKeyFrame(12.0);
        	key->Translation(ignition::math::Vector3d(-1.545,4.755,0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));


        	key = anim->CreateKeyFrame(20.0);
        	key->Translation(ignition::math::Vector3d(-2.367,7.285,0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
		
		key = anim->CreateKeyFrame(34.0);
        	key->Translation(ignition::math::Vector3d(-.927,2.853,0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));


	//set final location equal to starting location

        	key = anim->CreateKeyFrame(40.0);
        	key->Translation(ignition::math::Vector3d(-.309,.951, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
        	
        	
        
       		//set the animation
       		_parent->SetAnimation(anim);
       	}
       	
       	// Pointer to the model
    	private: physics::ModelPtr model;

    	// Pointer to the update event connection
    	private: event::ConnectionPtr updateConnection;
  };
  
  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(target5)
}

