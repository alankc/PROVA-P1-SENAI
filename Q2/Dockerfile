FROM amd64/ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

#software-properties-common allows to use add-apt-repository
#locales to set locales for ros
RUN apt update \
    && apt upgrade -y \
    && apt install -y \
    sudo \
    software-properties-common \
    locales \ 
    curl \
    python3 \
    python3-pip \
    bash-completion \
    nano \
    && rm -rf /var/lib/apt/lists/*


#FROM https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html
RUN locale-gen en_US en_US.UTF-8 \
    && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG=en_US.UTF-8

RUN add-apt-repository universe

RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# ros-humble-ros-base base development libs
# ros-dev-tools: colcon and ament
# for debug help ros-humble-rqt 
# for vizualization ros-humble-rviz2 
# python3-colcon-common-extensions is importantant to get colconon altocomplete
RUN apt update \
    && apt install -y \
    ros-humble-ros-base \
    ros-dev-tools \
    ros-humble-rqt \
    ros-humble-rviz2 \
    python3-colcon-common-extensions \ 
    && rm -rf /var/lib/apt/lists/*


#from: https://code.visualstudio.com/remote/advancedcontainers/add-nonroot-user
ARG USERNAME=isi_user
ARG USER_UID=1000
ARG USER_GID=$USER_UID
    
# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
    

USER $USERNAME

# Export of ros
RUN echo "source /opt/ros/humble/setup.bash\n" >> /home/$USERNAME/.bashrc

# Enable colcon autocomplete
RUN echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash\n" >> /home/$USERNAME/.bashrc

RUN mkdir -p /home/$USERNAME/ws_ros/src

# starts inside ws_ros
WORKDIR /home/$USERNAME/ws_ros

