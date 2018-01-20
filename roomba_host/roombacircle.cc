#include <gazebo/gazebo.hh>
#include <ignition/math.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

 namespace gazebo
{
  class RoombaCircle : public ModelPlugin
  {
  	public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
  	{
 
  
  		this->model = _parent;
  		
  			//animation
  			gazebo::common::PoseAnimationPtr anim(
  				//name animation
  				// set time
  				// put on loop
  				new gazebo::common::PoseAnimation("test",94.2,true));
 				
  		 	gazebo::common::PoseKeyFrame *key; //no idea what this line does lol
  		
		// this needs to be modeled correctly	
  		//set starting location of roombah
  		key = anim->CreateKeyFrame(0);
        	key->Translation(ignition::math::Vector3d(5, 0, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
        	
        	// set waypoint location after  seconds
        	key = anim->CreateKeyFrame(5.8875);
        	key->Translation(ignition::math::Vector3d(4.33,-2.5, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
        	
        	key = anim->CreateKeyFrame(11.775);
        	key->Translation(ignition::math::Vector3d(3.535,-3.535, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

        	key = anim->CreateKeyFrame(17.6625);
        	key->Translation(ignition::math::Vector3d(2.5, -4.33, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
		
		key = anim->CreateKeyFrame(23.55);
        	key->Translation(ignition::math::Vector3d(0,-5, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
        	
        	key = anim->CreateKeyFrame(29.4375);
        	key->Translation(ignition::math::Vector3d(-2.5,-4.33, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

		key = anim->CreateKeyFrame(35.325);
        	key->Translation(ignition::math::Vector3d(-3.535,-3.535, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

        	key = anim->CreateKeyFrame(41.2125);
        	key->Translation(ignition::math::Vector3d(-4.33, -2.5, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
		
		//Halfway point of the circle
		key = anim->CreateKeyFrame(47.1);
        	key->Translation(ignition::math::Vector3d(-5,0, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

		key = anim->CreateKeyFrame(52.9875);
        	key->Translation(ignition::math::Vector3d(-4.33,2.5, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
		
		key = anim->CreateKeyFrame(58.875);
        	key->Translation(ignition::math::Vector3d(-3.535,3.535, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

		key = anim->CreateKeyFrame(64.7625);
        	key->Translation(ignition::math::Vector3d(-2.5,4.33, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));
		// 3/4 Through the path
		key = anim->CreateKeyFrame(69.75);
        	key->Translation(ignition::math::Vector3d(0,5, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

		key = anim->CreateKeyFrame(76.5625);
        	key->Translation(ignition::math::Vector3d(2.5,4.33, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

		key = anim->CreateKeyFrame(82.425);
        	key->Translation(ignition::math::Vector3d(3.535,3.535, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

		key = anim->CreateKeyFrame(88.3125);
        	key->Translation(ignition::math::Vector3d(4.33,2.5, 0));
        	key->Rotation(ignition::math::Quaterniond(0, 0, 0));

		//set final location equal to starting location

        	key = anim->CreateKeyFrame(94.2);
        	key->Translation(ignition::math::Vector3d(5,0, 0));
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
  GZ_REGISTER_MODEL_PLUGIN(RoombaCircle)
}
 
