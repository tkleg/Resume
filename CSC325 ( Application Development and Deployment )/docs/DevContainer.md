## DevContainer Environment

### Introduction

#### What is a DevContainer?

A **DevContainer** is a **development environment** that use various **libraries** and other tools in order to eliminate the need to constantly be importing different **libraries**. When working in a **DevContainer** you can set any number of **libraries** to be built into the container so that they can be used through the **container**.

#### Why DevContainer for Flutter?

**Flutter** itself needs to be installed in a **development environment** for you to be able to use it. In the context of **Flutter** application development, **DevContainers** are useful because they can have the necessary **Flutter packages** installed upon creation so that **Flutter** can be worked with as soon as the **DevContainer** generates from its **base image**. A **DevContainer** is also useful for developing **Flutter applications** because you can put commands that need to be run for **Flutter** to work in the **devcontainer.json** file so that you do not need to manually enter them.

### DevContainer Configuration

#### Base Image

The base image used for the **DevContainer** in this repo is **Ubuntu-jammy**.

#### Additional Tools and Extensions in the Container

In the **devcontainer.json** file the only tool installed is the [Flutter SDK](https://www.scaler.com/topics/flutter-sdk/). It also has both the **Flutter** and **Dart** **VSCode** extensions listed so they will install automatically upon opening the **DevContainer**. Instructions to download both extensions and use basic **Flutter** features in **VSCode** can be found [HERE](https://docs.flutter.dev/tools/vs-code)

In the **Dockerfile**, several packages are installed to th **DevContainer** to allow for easy use such as **zip**, **git**, etc.

#### Configuration Settings

The **Dockerfile** has several configuration settings listed, most are commands to be run so that the **Flutter SDK** is installed and all dependencies are handled automatically by the **DevContainer**. Instructions for installing the **Flutter SDK** manually if you ever need to can be found [HERE](https://docs.flutter.dev/get-started/install).

### Integration with VSCode

The **DevContainer** integrates with **VSCode** in two main ways. 
1. The [Dev Containers VSCode extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) allows for the user to easily open **Docker Containers** in a **DevContainer** for easy development.
2. The [Docker extension](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker) allows for easy use of **Docker files** and integration with the **Docker** application downloaded on your computer so that a **DevContainer** can be run on your computer easily.
Additionally, **VSCode** also allows for the user to easily access any ports used by the **DevContainer**.

### Usage

#### Steps for starting the container

1. Open both [VSCode](https://code.visualstudio.com/download) and [Docker](https://www.docker.com/get-started/) on your computer. Install them first if neccessary.
2. Ensure both the **Dev Containers** extenstion and the **Docker** extension are installed on **VSCode**
3. Open the folder with your **Devcontainer configuration files** and any other files/folders you need to used within the container.
4. At the bottom left of **VSCode** hit the blue button and select **Reopen in Container** at the top. When opening the files, **VSCode** may also just prompt you to reopen in container, this option works to. Now the **DevContainier** will be started.

#### Editing Code

1. Editing code within a **DevContainer** is very simple. You simply need to save changes you make within files in the **DevContainer** and the changes will be saved when closing the **DevContainer**.

#### Running A Flutter Application

Code in **devcontainer.json** and **Dockerfile** run most of the commands needed to run a **Flutter application**. The steps you need to do manually each time are as follows.
1. Run **flutter create (any app name)** in the terminal to create an app.
2. Run **cd (app name entered before)** in the terminal to enter the app's directory.
3. Run **flutter run -d web-server** to start the Flutter application.
4. The application can now be accessed either through a link in the terminal output or through a port in the ports tab in VSCode.

### Challenges and Solutions

There were two main challenges encountered while setting up the DevContainer
1. Initially **Flutter** was not working immediately upon starting the **DevContainer**. After much trial and error I was able to set specific commands to run in the **Dockerfile** that do things such as resolve **dependencies** and change permissions necessary to create and use a **Flutter application**.
2. File Structure was also an issue, although not nearly as impactful. I mistakenly had a **.devcontainer** folder within another **.devcontainer** folder so the file structure of the **DevContainer** was slightly confusing and more complicated than it should have been.

### Conclusion

The benefits of using **DevContainer** for this project is that there is no need to change **configutations** for tools such as **Flutter** whenever you want to edit something for the project since the **DevContainer** handles all of that upon starting. Additionally, using a **DevContainer** allows for **Flutter applications** to be generated quickly with just a single command. Saving time for testing.


