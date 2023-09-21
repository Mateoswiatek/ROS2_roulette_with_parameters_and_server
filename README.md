# roulette_with_parameters_and_server
## Introduction and brief description
The natural progression in learning ROS2 after completing the mini projects in 'ROS2_others_project'. In this project, I wrote a Topic that utilized a pre-existing interface. A Service was also added To facilitate the integration of various data transfer solutions in ROS2. Appropriate parameters were introduced to enhance project scalability. Naturally, Launch Files were implemented as well (more complex ones can be found in the 'robots_spam' repository within 'ROS2_other_projects'). Completing this mini project instilled excellent coding practices, making it much easier to scale future projects.

A more complex project in another repository, 'ROS2_follow_turtle_robot'.

## Technologies Used

Utilized Features:
- Packages,
- Nodes,
- Callbacks,
- Topics
- Services,
- Interfaces (Msg and Srv)
- Threads,
- Parameters,
- Launch Files

## Full Description

The project consists of two types of Nodes:
**"number_publisher"** - This Node publishes a random number between 0 and a specified parameter (default value is 10) to a Topic. The frequency of generating random numbers is also a parameter passed to the Node.
**"number_counter"** - This Node processes the received number. If it is below a specified value, it outputs a win message. Additionally, it keeps count of the number of "draws" and sends this count to another Topic. The Node also provides a service to reset the count of drawn numbers."

## Potential for Further Development / Ideas
- Counting the current probability.
- Adding a range of "winning" numbers instead of just one.
