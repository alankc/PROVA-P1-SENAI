from setuptools import find_packages, setup

package_name = 'pkg_2'

setup(
    name=package_name,
    version='0.0.1',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='isi_user',
    maintainer_email='cechinel.a.k@gmail.com',
    description='Pacote que simula leitura de um sensor com buffer circular',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'sensor_reader = pkg_2.sensor_reader:main'
        ],
    },
)
