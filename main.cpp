#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main (){
    ifstream file ("data.bin", ios::binary | ios::ate);
    ofstream file2 ("output.bin", ios::binary | ios::trunc);

    if (!file.is_open() || !file2.is_open()){
        cerr<<"File failed to open !!"<< endl;
        return 1;
    }
    else
        cout<<"File succesfully openned !!!"<< endl;

    file.seekg(0, ios::end);//seekg moves file pointer to the specific place
    size_t fileSize = file.tellg();// tellg return current position file pointer
    file.seekg(0, ios::beg);

    size_t CHUNK_SIZE = min(fileSize, static_cast<size_t>(8));//chunk extraxtion by 10 bytes
    vector<char> buffer8(CHUNK_SIZE);
    cout<< "File size: " << fileSize <<"bytes" <<endl;
    cout<<"Reading file in chunks of " << CHUNK_SIZE << " bytes: " << endl;

    while(file.read(buffer8.data(),CHUNK_SIZE)){
        streamsize byteRead = file.gcount();
        cout << "Read "<< byteRead << " bytes...." << endl; 
    }

    streamsize remaining = file.gcount();
    if(remaining > 0){
        file.read(buffer8.data(),remaining);
        cout <<"Read "<< remaining << " bytes...." << endl;
    }

    file.clear();
    file.seekg(0, ios::beg);

    //extracting the first 10 bytes strating from the fifth

    file.seekg(5, ios::beg);
    size_t extractSize =  min(fileSize, static_cast<size_t>(10));
    vector<char> extarctedBuffer(extractSize);

    if(file.read(extarctedBuffer.data(), extractSize)){
        cout<< "Extarcted "<< extractSize << "bytes from the file (starting from the 5th byte):\n";
        for (char c : extarctedBuffer){
            cout<< static_cast<int> (c) << " ";
        }
        cout << endl;
    }else{
        cerr << "Failed to extract data!" << endl;
        return 1;
    }



    //write into output.bin
    const char data[] = "this is when fourth time ios:: trunc";
    file2.write(data, sizeof(data) -1);
    file2.close();


    vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);
    file.clear();
    file.seekg(0, ios::beg);

    //READ from file2
    ifstream readFile("output.bin", ios::binary);
    if(!readFile){
        cerr << "Failed to open output.bin for reading!" << endl;
        return 1;
    }

    if(!file.read(buffer.data(), fileSize)){
        cerr << "Error reading file!"<< endl;
        return 1;
    }

    cout<< "File data in the vector(data.bin/ file): "<<endl;
    for(char c : buffer){
        cout << static_cast<int>(c) << " ";
    }
    /*more readable output
        for(char c : buffer){
        if(isprint(c))  cout << c << " ";
        else cout << "[" << static_cast<int>(c) <<"]";
    }*/
    cout<< endl;

    //get size of file2
    readFile.seekg(0, ios::end);
    streampos file2Size = readFile.tellg();
    cout<< "File2 size(output.bin): " << file2Size <<"bytes" <<endl;
    readFile.seekg(0, ios::beg);

    //read the content file2
    vector<char> outputData(file2Size);
    readFile.read(outputData.data(), file2Size);
    readFile.close();

    cout<< "content in output.bin: " <<endl;
    

    for(char v : outputData){
        cout<< /*static_cast<int>*/v <<"  " ;
    }
    
    file.close();
    return 0;
}