import serial
import serial.tools.list_ports as port_list
import time
import struct
#from std_msgs.msg import Int32MultiArray

stm = ...
sensor_data_shape = [8, 8, 8, 4, 4, 4]
#my_array_for_publishing = Int32MultiArray()


def clamp(value: float):
    return int(min(max(value, 1000.0), 2000.0))


def find_stm():
    stm_product = 'STM32 STLink'
    stm_dev_port = ''
    ports = list(port_list.comports())
    for p in ports:
        if p.product == stm_product:
            stm_dev_port = p.device

    if stm_dev_port == '':
        raise Exception("STM not found!")
    else:
        print(f"Found STM at {stm_dev_port}")
        return stm_dev_port


def callback(data):
    # rospy.loginfo(rospy.get_caller_id() + "I heard %f %f", data.linear.x, data.angular.z)

    velocity = clamp(1500.0 + data.linear.x * 74.0)  # 74 shoud produce real velocity in m/s
    angularVelocity = clamp(1500.0 - data.angular.z * 160.0)  # 3.14 rad/s max angular speed

    # rospy.loginfo(rospy.get_caller_id() + "In ints %i %i", velocity, angularVelocity)
    try:
        output = b'AA' + str(velocity).encode('utf-8') + str(angularVelocity).encode('utf-8')
        stm.write(output)

        # Read only when writing is done
        sensor_data = read_serial()
     #   if sensor_data != None:
    #        publish_sensor_data(sensor_data)

    except Exception as e:
        print(e)


def read_serial():
    line_in = b''
    try:
        # read whole buffer and find the last line in
        receive = stm.read_all()
        print(receive)
        if len(receive) >= 37:
            for i in range(len(receive) - 1, 0, -1):

                if receive[i - 1:i] == b'\n' and i - 37 >= 0:
                    line_in = receive[i - 37:i]
                    # print(line_in)
                    break

        if len(line_in) == 29:
            input = []
            index = 0

            for d in sensor_data_shape:

                input.append(int(float(line_in[index:index + d].split(b'\x00', 1)[0].decode('utf-8'))))
                index += d

            return input

    except Exception as e:
        print(e)





def main():
    global stm

    while(1):
        with serial.Serial("COM12", 115200, timeout=0) as stm:

            time.sleep(1)

            print(read_serial())
            #stm.reset_input_buffer()
            #stm.reset_output_buffer()
            # while not rospy.is_shutdown():

main()

# rospy.sleep(0.01)



