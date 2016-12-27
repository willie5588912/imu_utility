iCeiRA imu utility
============

install
============

	cd ~/ws/src
	git clone -b indigo-devel https://github.com/KristofRobot/razor_imu_9dof
	cd razor_imu_9dof/config
	cp razor.yaml my_razor.yaml
	vi my_razor.yaml
	cd ../../..
	catkin_mak

launch
============

	roslaunch razor_imu_9dof razor-pub-and-display.launch
	rosrun imu_utility ira_imu

ref:

http://wiki.ros.org/razor_imu_9dof