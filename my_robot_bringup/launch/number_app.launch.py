from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription()
    
    remap_number_topic = ("number", "my_number_topic")

    number_publisher_node = Node(
        package="activity_002_topic_cpp",
        executable="number_publisher",
        name="my_number_publisher",
        remappings=[
            remap_number_topic
        ],
        parameters=[
            {"publish_frequency": 10.0},
            {"ceil_of_random_number": 20}
        ]
    )

    number_counter_node = Node(
        package="activity_002_topic_cpp",
        executable="number_counter",
        remappings=[
            remap_number_topic,
            ("number_count", "nowe_publikowanie")
        ]
    )

    ld.add_action(number_publisher_node)
    ld.add_action(number_counter_node)
    return ld