# CSC325 Source Control
Steps to setup and use the containerized development environment to run a flutter web application.
Note: If at anypoint in **VSCode** the terminal is not appearing and you need it to be, hit `` Ctrl+` ``
1. Ensure that both [VSCode](https://code.visualstudio.com/download) and [Docker Desktop](https://www.docker.com/products/docker-desktop/) are installed on your computer.
2. Open Docker Desktop, this must stay open in the background for the devcontainer to work properly (you can minimize it if you want).
3. Open **VSCode** and make sure to install the [Dev Containers Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) and the [Docker Desktop Extension](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker)
4. Open the **Explorer** tab in **VSCode** at the top left of the screen. Then select **Clone Repository**. Then paste `https://github.com/tkleg/CSC325Pipeline.git` into the field at the top of the screen and hit enter.
5. Click the blue button at the buttom left of **VSCode**, then click **Reopen in Container** in the drop down menu from the top of the screen.
6. In the terminal, run `cd app` to cd into the app's directory
7. In the terminal, run the command `flutter run -d web-server` to run the app
8. Finally, click the localhost link that appears in the terminal ( this may take around a minute to appear).
