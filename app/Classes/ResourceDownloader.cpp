//
//  ResourceDownloader.cpp
//  cluburo
//
//  Created by TakuKobayshi on H29/03/07.
//
//

#include "ResourceDownloader.hpp"

using namespace cocos2d::network;

// HTTP通信
void ResourceDownloader::download(std::string url, const std::function<void(std::string)>& onDownloadCompleted) {
    auto request = new HttpRequest();
    
    request->setUrl(url);
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(ResourceDownloader::onHttpRequestCompleted));
    
    HttpClient::getInstance()->send(request);
    request->release();
}

// コールバックメソッドの中で受信したファイルを保存する
void ResourceDownloader::onHttpRequestCompleted(HttpClient* client, HttpResponse* response, const std::function<void(std::string)>& onDownloadCompleted) {
    if (!response->isSucceed()) {return;}
    
    std::string filePath = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "image.png";
    
    std::vector<char> *buffer = response->getResponseData();
    std::ofstream ofs;
    ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
    ofs.write(&(buffer->front()), buffer->size());
    ofs.flush();
    ofs.close();
    onDownloadCompleted(filePath);
}
