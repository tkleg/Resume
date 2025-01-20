## Source Code Version Control Tools

### Introduction

#### Importance of Version Control
```Version Control``` is crucial to software development mainly because it prevents developers from breaking software accidentally and not being able to revert back to a version where it was working. Additionally, it allows for the easy adding of features without interfering with the base branches.

#### Role of Version Control
As mentioned above, ```Version Control``` is crucial to avoid breaking a program on accident. It also makes software development easier by allowing developers to look at many different versions of the software to be able to track when certain changes are made. Finally, it makes collaboration much easier because it allows for developers to see what changes other developers made to a software application.

### Repository Setup

#### Repository Structure
My repository is largely just using the main branch. This is because the actual development of the application was completed prior to using a ```GitHub``` repository. The only changes needed to be made to the repo are the additions of documentation files and YAML files. Since these files are all added one at a time and have no chance of breaking the repo, there is no need to use branching at the moment. However, once the ```build.yaml``` file works, the repo will be copied to another branch in case the need to make alterations to it arises.

#### Repository File Structure
- ```./devcontainer```: Contains ```devcontainer.json``` and ```DockerFile```. It hosts the files necessary for the ```DevContainer``` to build properly and have the proper tools.
- ```./github```: Contains ```YAML``` files that allow for proper build and deployment of the app.
- ```./app```: Contains the flutter application. This includes but is not limited to test files, source code, and code to allow the app to work on various operating systems.
- ```./docs```: Contains markdown files which explain various parts of the repository, its contents, and how to use the repository and its contents.
- ```README.md```: This contains instructions for running the ```flutter web application``` in a ```DevContainer``` via their computer.

#### Repository Integration with DevContainer and CI/CD Pipeline
Every branch in the repository contains the DevContainer configuration files and the files for the default app (the app will be changed to the final app at a later date). This makes it so that upon cloning any branch in the repo you can instantly open it up in a ```DevContainer```. This allows for easy testing of the flutter web apps and development of the apps.

#### Standards and Convections
So far the commit messages are numbered starting at #1 for every new thing thats being added and requires troubleshooting. Other than that the commit messages are kept short and detail what changes were made to the repo.

### Commmon Commands and Usage
1. ```git clone *link to repo branch*``` ( This clones into a repo. Alternatively however you can do this with the source control tab of VSCode )
2. ```cd app``` ( Goes into the app directory from the base directory of a branch so that the web app can be built and ran from VSCode )
3. ```clear``` ( Clears the terminal screen to decrease clutter and increase readibility of the terminal )
4. ```flutter create app``` ( Creates the flutter base app )
5. ```flutter run -d web-server``` ( Compiles the app's source code and provides a link where the web app can be accessed on your device )
6. ```flutter pub get``` ( Checks for dependencies )
7. ```flutter --version``` ( Checks if flutter is installed and accessible in the current directory )
8. ```git branch branch2``` ( Creates a new branch called branch2 which starts as a copy of the current branch, also changes the current branch to branch2 )
9. ```git merge branch2``` ( Merges branch2 into the current branch )
10. ```git status``` ( Tells you what the current branch is )
11. ```git add *files*``` ( Stages changes to certain files )
12. ```git commit -m *message*``` ( Commits all staged changes with an user written commit message )
13. ```git push``` ( Pushes commited changes to the current repo )

### Collaboration Features
Pull requests help facilitate collaboration amoung team members because it allows any team member to view the files that someone else has worked on. Version control tools facilitaties collaboration amoung team members through code reviews because it is very easy to add text files to a repo with comments and it allows team members to make a branch of another branch with changes they think are needed while not altering the original branch. Version control tools facilitate conflict resolution because it is very easy to view multiple branches side by side and compare them to figure out which works best for the team.

### Challenges and Solutions
1. There was a lot of trouble getting the ```GitLab``` repo to take files through pushing on ```VSCode``` as the bash commands necessary had confusing syntax. The issue was fixed by switching over to using a ```GitHub``` repo because it is much easier to work with in ```VSCode``` and it has the workflow feature. 
2. Since using ```GitHub```, the only issue encountered was with merging through terminal commands. It was decided that it was best to simply revert to doing merges through ```GitHub``` direcctly as it is much simpler to do and saves time.

### Conclusion
The benefits of using my chosen version control system ```(GitHub)``` for the project is that it is insanely easy to work with ```GitHub``` repos in ```VSCode```. ```VSCode``` makes it so that I can clone into a repo, change branches, create new branches, and commit and push changes without ever touching the terminal. The merging is slightly more difficult but as mentioned before, it is incredibly easy to do through ```GitHub``` itself. An additional benefit of using ```GitHub``` is that it can run the workflows that are being used in the project to build the application. An important insight that has been learned from the project so far is that ```GitHub``` is an incredibly useful tool for developing nearly any kind of software.