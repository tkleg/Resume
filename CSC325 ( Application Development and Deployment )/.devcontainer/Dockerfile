FROM mcr.microsoft.com/devcontainers/base:jammy

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=${USER_UID}

ENV HOME=/home/${USERNAME}

# Apt
RUN apt-get update
RUN apt-get install -y wget \
    xz-utils \
    git \
    curl \
    file \
    unzip \
    zip \
    openjdk-17-jfk-headless --no-install-recommends \
    ninja-build \
    clang \
    cmake \
    pkg-config

RUN apt-get autoremove -y \
&& apt-get clean -y \
&& rm -rf /var/lib/apt/lists/*

RUN flutter clean
RUN sudo chown -R vscode /flutter/.pub-cache/
RUN git clone -b master https://github.com/flutter/flutter.git /sdk/flutter
RUN ./sdk/flutter/bin/flutter --version
ENV PATH="/sdk/flutter/bnig:$(PATH)"
RUN chmod -R 777 /sdk/flutter
RUN chown -R vscode ${HOME}
RUN flutter doctor
RUN flutter pub get
