## Pipeline.md

This section details the Continuous Integration/Continuous Deployment (CI/CD) pipeline established for our Flutter web application. The CI/CD pipeline automates critical stages of the development process, ensuring consistent builds, testing, and deployment upon code changes.

### CI/CD Pipeline Environment

-  Our CI/CD pipeline leverages a cloud-based infrastructure ( Stored in a GitHub repository )for scalability and ease of management.
-  The devcontainers we use operate on **Ubuntu Linux**, a widely supported operating system for development tools and software builds.
-  Network configurations ensure secure communication between the pipeline, our code repository, and any external services required during the build and deployment phases.

### CI/CD Pipeline Tools

We have chosen **GitHub Actions** as our primary CI/CD pipeline tool due to the following factors:

* Integration with **GitHub**: Since our project is hosted on GitHub, tight integration with **GitHub Actions** simplifies workflow management. **Github Actions** allows the user to easily look at how their workflows are operating, enabling them to make the necessary adjustments.
* Ease of Use:  **GitHub Acions** offers a user-friendly interface and extensive documentation, making it accessible for our development team.
* Scalability:  **GitHub Actions** scales effortlessly with our project's needs, allowing us to add more workflows or jobs as complexity increases. This is made very simple by the use of **branches** and **issues**.

While **GitHub Actions** offers a comprehensive suite of features, some limitations exist:

* Limited Customization:  Compared to enterprise-grade solutions like **Jenkins**, **GitHub Actions** offers less flexibility for complex workflows.
* Limited Resource Control:  Resource allocation for pipeline jobs might be less granular than dedicated **CI/CD servers**.

We acknowledge these limitations, but for our project's scope and current development stage, **GitHub Actions** provides a strong balance of features and ease of use.

### Automation Process

Our **CI/CD pipeline** automates the following stages:

1. **Code Checkout:** Upon a push event to the a branch, the workflow automatically checks out the latest code from the **GitHub repository**.
2. **Dependency Installation:** The pipeline utilizes the `flutter pub get` command to install project dependencies, ensuring a consistent development environment across builds.
3. **Building:**  The `subosito/flutter-action@v1` action with the `stable` channel is used to set up the **Flutter environment** and build the source code. The build command `flutter build web` generates the production-ready web application artifacts.
4. **Unit Testing (Optional):**  Following the build, unit tests can be integrated into the pipeline using the `flutter test --coverage` command. This step verifies core functionalities work as expected. Additionally, it tracks how many lines of code and how many methods were checked by the tests.
5. **Code Coverage Reporting (Optional):**  If unit testing is included, the `zgosalvez/github-actions-report-lcov@v3` action can be used to upload code coverage reports and generate comments on pull requests. This requires defining the `GITHUB_TOKEN` secret in your repository settings.
6. **Deployment:**  The final stage involves deploying the built artifacts (located in the `./app/build/web` directory) to **GitHub Pages**. The `peaceiris/actions-gh-pages@v3` action automates this process, leveraging the defined `GITHUB_TOKEN` for authentication.

**Conclusion**

This **CI/CD pipeline** establishes a foundation for automated testing, building, and deployment of our Flutter web application. Utilizing **GitHub Actions** and a cloud-based infrastructure ensures a scalable and efficient workflow. We will continuously monitor and improve the pipeline as our project evolves, potentially integrating additional tools or modifying the automation process for optimal delivery.
