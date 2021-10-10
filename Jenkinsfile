pipeline{
    agent any

    environment{
        REPO_NAME = 'HTTP_Messenger_Logger'
        // LIBRARY_PATH = 'C:\\Users\\akork\\Desktop\\HttpMessengerLogger\\vcpkg'
        // DLL_PATH = "${LIBRARY_PATH}\\installed\\x64-windows\\debug\\bin\\cpprest_2_10d.dll"
        
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
                    artifacts: "/",
                    fingerprint: true
                )
            }
        }
    }
}
