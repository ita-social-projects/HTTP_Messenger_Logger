pipeline{
    agent any

    environment{
        REPO_NAME = 'HTTP_Messenger_Logger'
    }

    stages{
        stage('Preparing the directory'){
            steps{
                dir(env.REPO_NAME){
                    bat "echo '======================CHECKOUTING========================='"
                    cleanWs()
                    checkout scm
                }
            }
        }
        stage('Build'){
            steps{
                dir(env.REPO_NAME){
                    bat "echo '======================BUILDING========================='"
                    bat "cmake --version"
                    bat "cmake . -B build"
                    bat "cmake --build build"
                }
            }
        }
    }
    post{
        success{
            script{
                archiveArtifacts(
                    artifacts: "/${env.REPO_NAME}/build/Debug/*.lib, /${env.REPO_NAME}/include/*.h",
                    fingerprint: true
                )
            }
        }
    }
}
