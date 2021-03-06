//
//  imageStore.swift
//  Assignment5
//
//  Created by Robbie Korneta on 11/19/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import Foundation
import UIKit

class ImageStore {
    
    let imageCache = NSCache<NSString, AnyObject>()
    
    func downloadImage(with urlString: String, completion: @escaping (_ image: UIImage?) -> Void) {
        
        if urlString == "None" {
            completion(UIImage(named: "default.png"))
        } else if let cachedImage = imageCache.object(forKey: urlString as NSString) as? UIImage {
            completion(cachedImage)
        } else {

            weak var weakSelf = self
            
            if let url = URL(string: urlString) {
            
                let task = URLSession.shared.dataTask(with: url) {
                    (data, response, error) in
                    
                    let httpResponse = response as? HTTPURLResponse
                    
                    if httpResponse!.statusCode != 200 {
                        // Perform some error handling
                        // UI updates, like alerts, should be directed to the main thread
                        DispatchQueue.main.async {
                            print("HTTP Error: status code \(httpResponse!.statusCode)")
                            completion(UIImage(named: "default.png"))
                        }
                    } else if (data == nil && error != nil) {
                        // Perform some error handling
                        DispatchQueue.main.async {
                            print("No data downloaded for \(urlString)")
                            completion(UIImage(named: "default.png"))
                        }
                    } else {
                        // Download succeeded
                        if let image = UIImage(data: data!) {
                            DispatchQueue.main.async {
                                weakSelf!.imageCache.setObject(image, forKey: urlString as NSString)
                                completion(image)
                            }
                        } else {
                            DispatchQueue.main.async {
                                print("\(urlString) is not a valid image")
                                completion(UIImage(named: "default.png"))
                            }
                        }

                    }
                }
                
                task.resume()
            } else {
                DispatchQueue.main.async {
                    print("\(urlString) is not a valid URL")
                    completion(UIImage(named: "default.png"))
                }
            }
        }
    }
    
    func clearCache() {
        imageCache.removeAllObjects()
    }
}

