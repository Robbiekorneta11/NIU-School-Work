//
//  PresidentDetailViewController.swift
//  Assignment4
//
//  Created by Robbie Korneta on 11/5/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import UIKit

class PresidentDetailViewController: UIViewController {

    @IBOutlet weak var presidentNameLabel: UILabel!
    @IBOutlet weak var presidentNumberLabel: UILabel!
    @IBOutlet weak var presidencyDatesLabel: UILabel!
    @IBOutlet weak var nickamesLabel: UILabel!
    @IBOutlet weak var politicalPartyLabel: UILabel!
    @IBOutlet weak var presidentImageView: UIImageView!
    
    var imageStore: ImageStore?
    
    let numberFormatter = NumberFormatter() // Format number
    
    // Handles the UI when the view is loading
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        configureView()

    }
    
    /*
     *  Sets up the view to display the presidential data
     */
    
    func configureView() {
        
        if let detail = detailItem {
            
            numberFormatter.numberStyle = .ordinal // Set number formatter to 1st, 2nd, etc.
            
            // Get image and display
            if let presidentImageView = presidentImageView, let imageStore = imageStore {
                imageStore.downloadImage(with: detail.imageURL, completion: {
                    (image: UIImage?) in
                    
                    presidentImageView.image = image
                    
                })
                
            }
            
            /*
             *  Set each label to its respective value from the json file
             */
            
            if let label = presidentNameLabel {
                
                label.text = detail.name
                
            }
            
            if let label = presidentNumberLabel {
                
                label.text = "\(numberFormatter.string(from: NSNumber(value: detail.number)) ?? "0") President of the United States"
                
            }
            
            if let label = presidencyDatesLabel {
                
                label.text = "(\(detail.startDate) to \(detail.endDate))"
                
            }
            
            if let label = nickamesLabel {
                
                label.text = detail.nickname
                
            }
            
            if let label = politicalPartyLabel {
                
                label.text = detail.politicalParty
                
            }
            
        }
        
    }
    
    var detailItem: President? {
        
        didSet {
            // Update the view.
            configureView()
            
        }
        
    }
    
    override func didReceiveMemoryWarning() {
        
        imageStore?.clearCache()
        
    }

}
