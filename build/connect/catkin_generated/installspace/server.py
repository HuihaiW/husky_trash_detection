#!/usr/bin/env python2
# license removed for brevity
import socket
import rospy
from std_msgs.msg import String

def service():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        hello_str = "hello world %s" % rospy.get_time()
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        rate.sleep()


    # pub = rospy.Publisher('chatter', String, queue_size=10)
    # rospy.init_node('talker', anonymous=True)
    # rate = rospy.Rate(10)
    # print("step 1")
    # # while not rospy.is_shutdown():
    # #     hello_str = "hello world %s" % rospy.get_time()
    # #     rospy.loginfo(hello_str)
    # #     pub.publish(hello_str)
    # #     rate.sleep()


    HOST = "127.0.0.1"
    PORT = 65432
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        i = 0
        with conn:
            print(f"connected by {addr}")
            while True:
                data = conn.recv(1024)
                i+=1
                if data:
                    if not rospy.is_shutdown():
                        hello_str = data
                        rospy.loginfo(hello_str)
                        pub.publish(hello_str)
                        rate.sleep()
                    # print(i, data)
                    conn.sendall(data)

if __name__ == '__main__':
    try:
        service()
    except rospy.ROSInterruptException:
        pass
