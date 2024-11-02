import rclpy
from rclpy.node import Node
from collections import deque
from random import random
import numpy as np
from q2_interfaces.srv import SensorReaderClean
from q2_interfaces.srv import SensorReaderData

class SensorReader(Node):

    def __init__(self):
        super().__init__('sensor_reader')

        self.circular_buffer_sensor = deque(maxlen=5)
        self.circular_buffer_service = deque(maxlen=64)

        self.declare_parameter('sensor_period', 1.0)
        timer_period = self.get_parameter('sensor_period').get_parameter_value().double_value
        if (timer_period < 0):
            timer_period = 1.0

        self.timer = self.create_timer(timer_period, self.sensor_simulation)

        self.srv_clear = self.create_service(SensorReaderClean, '/clear_buffer', self.clear_buffer)
        self.srv_get = self.create_service(SensorReaderData, '/get_buffer', self.get_buffer)


    def sensor_simulation(self):
        self.circular_buffer_sensor.append(random())
        #add to the buffer service only after having 5 values
        if (len(self.circular_buffer_sensor) == self.circular_buffer_sensor.maxlen):
            sensor_filter = np.mean(self.circular_buffer_sensor)
            self.circular_buffer_service.append(sensor_filter)


    def clear_buffer(self, request, response):
        self.circular_buffer_service.clear()
        response.response_msg = "Buffer Cleaned"
        response.status = True
        return response

    def get_buffer(self, request, response):
        for data in self.circular_buffer_service:
            response.readings.append(data)
        return response


def main(args=None):
    rclpy.init(args=args)
    minimal_publisher = SensorReader()
    rclpy.spin(minimal_publisher)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()