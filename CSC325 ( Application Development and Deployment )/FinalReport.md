## CI/CD Pipeline for Flutter Application

This report details the development and deployment process for a Flutter web application using a CI/CD pipeline. It covers the various tools and configurations utilized to achieve automated builds, tests, and deployments.

### Introduction

Continuous Integration and Continuous Delivery (CI/CD) pipelines play a crucial role in modern software development. They automate the build, test, and deployment processes, enabling faster development cycles, improved software quality, and reduced manual intervention. This project focuses on building a CI/CD pipeline for a Flutter application, providing students with hands-on experience with these concepts.


### DevContainer Configuration

#### Base Image

The base image used for the **DevContainer** in this repo is **Ubuntu-jammy**.

#### Additional Tools and Extensions in the Container

In the **devcontainer.json** file the only tool installed is the [Flutter SDK](https://www.scaler.com/topics/flutter-sdk/). It also has both the **Flutter** and **Dart** **VSCode** extensions listed so they will install automatically upon opening the **DevContainer**. Instructions to download both extensions and use basic **Flutter** features in **VSCode** can be found [HERE](https://docs.flutter.dev/tools/vs-code)

In the **Dockerfile**, several packages are installed to th **DevContainer** to allow for easy use such as **zip**, **git**, etc.

#### Configuration Settings

The **Dockerfile** has several configuration settings listed, most are commands to be run so that the **Flutter SDK** is installed and all dependencies are handled automatically by the **DevContainer**. Instructions for installing the **Flutter SDK** manually if you ever need to can be found [HERE](https://docs.flutter.dev/get-started/install).

### Source Code Version Control Tools

The project utilizes **Git** as the version control system for managing the source code of the **Flutter** application. **Git** allows for tracking changes, collaborating with others, and reverting to previous versions if necessary.

The integration with the **CI/CD Pipeline** includes:

* A remote GitHub repository to store the codebase.
* The **CI/CD Pipeline** triggers on pushes to the main branch where some files are changed other than **.md** or **.txt** files in the remote repository.
* Branches and issues are used extensively to add features or fix broken parts of the application and/or pipeline without the risk of ruining previously working code.

This integration enables the pipeline to access the latest code changes and automate the build, test, and deployment processes upon each push.



### CI/CD Pipeline Environment

The CI/CD pipeline is implemented using **GitHub Actions**. The `build.yml` file defines the workflow for the pipeline. Here's a breakdown of the pipeline stages based on the **YAML** file:

1. **Trigger:** The pipeline triggers on any push to the `main` branch, excluding changes to markdown (`.md`) and text (`.txt`) files. This ensures the pipeline focuses on code changes relevant to application or pipeline functionality.
2. **Build:** This stage performs the following actions:
    * Checks out the code from the Git repository.
    * Sets up the Flutter development environment using the `subosito/flutter-action@v1` action
    * Installs project dependencies using `flutter pub get`.
    * Sets up code coverage with `lcov`.
    * Runs unit tests with code coverage generation using `flutter test --coverage`.
    * Uploads the generated code coverage report using the `fjlopezs/lcov-reporter-action@v1.0.0` action.
    * Builds the web application using `flutter build web`.
3. **Web Deploy - GitHub Pages:** This stage deploys the built web application artifacts to GitHub Pages using the `peaceiris/actions-gh-pages@v3` action. This allows for the link to the application to be published in a **GitHub Actions** workflow that runs upon the completiong of the workflow in `build.yml`.

This pipeline automates the entire build, test, and deployment process for the **Flutter Web Application** upon most pushes to the `main` branch.

### CI/CD Tools

The project likely utilizes the following CI/CD tools based on the information provided:

* **GitHub Actions:** A cloud-based CI/CD service offered by GitHub that allows defining workflows for automated builds, tests, and deployments. The `Main Pipeline.yml` file defines the workflow for this project's CI/CD pipeline.
* **subosito/flutter-action:** A GitHub Actions action that sets up the Flutter development environment.
* **fjlopezs/lcov-reporter-action:** A GitHub Actions action that uploads code coverage reports generated during testing.
* **peaceiris/actions-gh-pages:** A GitHub Actions action that automates deployments to GitHub Pages.

These tools work together within the CI/CD workflow to achieve automated builds, tests, and deployments.


### Deployment Environment

The application is deployed to **GitHub Pages**, a static web hosting service offered by **GitHub**. The `build.yml` file utilizes several tools such as `lcov` to help run the pipelines various steps. This deployment environment gives us a code coverage report and gives us a link to access the application via a web browser.

### Flutter Web Application

The application is a simple game of TicTacToe. It it written entirely in the ```Dart``` coding language.

#### Functionality of Application

The app is quite simple in design. The squares are generated with a list within a grid to allow for them to show as a 3 by 3 square. Due to the design of the list widget generation in dart, the program automatically tracks the index of the button hit so that we can correctly mark the correct sqaure as being hit. We use a conditional operator to show the winning game message. After every click the game marks the selected square if not already and checks for a win. If it finds a win then it sets a boolean variable called ```gameOver``` to true, causing a end game message to be displayed at the next build of the page.

#### Testing of Application

The testing for the application is quite simple and still has over 90% code coverage reached. The way it works is by putting all of the buttons on the screen in a list. Then it goes through them one by one clicking on them. At each iteration the test file checks that the appropriate String is showing who's turn it is. After 7 clicks, player X will have won since the same buttons are clicked everytime the test runs. After the 7 clicks, we simply look for the proper end game messages.

#### Deployment process

```build.yml``` does many things to allow the app to deploy properly.
1. Dependencies are isntalled with the ```flutter pub get``` command.
2. ```lcov``` is setup to allow for code coverage reporting
3. ```flutter test --coverage``` is run to test the application and generate a code coverage report
4. A file is generated with the code coverage report so that we can view it
5. ```flutter build web``` builds the web application
6. The app is publishede to **GitHub Pages** so that it can be viewed

### Conclusion

Overall, the project taught me alot about the process of developing software. I learned how useful **DevContainers** are to solve the **It works on my machine** issue, how **GitHub** can be used to do version control, how **CI/CD Pipelines** are incredibly useful tools that will automate building and deployment processes, and much more. 

#### Issues Encountered
-   How to get a **DevContainer** running in **VSCode**
    -   This was fixed with simply a lot of trial and error.
-   I had to run ```sudo chown -R vscode /flutter/.pub-cache/``` everytime I started the container even though it was in my ```postCreateCommands```
    -   This issue was happenning because ```flutter clean``` ran after it in the ```postCreateCommands```, this command essentially erased the effect that ```sudo chown -R vscode /flutter/.pub-cache/``` had, causing it to be have to ran again. The issue was solved by removing ```flutter clean``` from the container's ```postCreateCommands```
-  How to publish my code to a **GitHub** repository ( by far the most stressful part of the entire class )
    -   This took me forever to figure out. Initially I used a Mercer ran ```GitLab``` server to do my **Source Control** but I switched to **GitHub** to take advantage of **GitHub Actions** and another reason I cannot recall
-  How to write the ```build.yml``` file to successfully deploy my application.
    -   This was a long process because it was still being worked on while broken pretty much. I had to remove the ```flutter test --coverage``` command to allow for the the workflow to run. I also had issues with my app being deployed. This was solved by changing the publishing directory of the deployment step in the workflow.


#### Potential Improvements

-   Upgrading the app so that it can be played online between two players
    -   I think this is simply quite far beyond what was in the scope of the class and the application was working just fine.
-   Upgrading the test for the app so that several runs of the app are processed with different outcomes
    -   This seemed somewhat unneccessary since the code coverage is over 90%, also it would have been very difficult since I would have to learn how to do all of it in Dart, which would take a long time.
-   Getting the Code Coverage report to automatically publish to a web browser page
    -   This was not required to be done for the assignment but I tried it anyway and it was too difficult so I decided not to implement this into the application.
