//
//  PresidentTableViewCell.swift
//  Assignment4
//
//  Created by Robbie Korneta on 11/5/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import UIKit

class PresidentTableViewCell: UITableViewCell {

    @IBOutlet weak var presidentNameLabel: UILabel!
    @IBOutlet weak var politicalAffiliationLabel: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
