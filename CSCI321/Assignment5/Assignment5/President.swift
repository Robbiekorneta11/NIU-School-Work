//
//  President.swift
//  Assignment4
//
//  Created by Robbie Korneta on 11/5/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import Foundation

// Represents a president
class President: Decodable {
    
    var name = ""           // Name of president
    var number = 0          // Number of president
    var startDate = ""      // Start date of president
    var endDate = ""        // End date of president
    var nickname = ""       // Nickname of president
    var politicalParty = "" // Political party of president
    var imageURL = ""
    
    // Match keys from file to each variable
    private enum CodingKeys: String, CodingKey {
        
        case name = "Name"
        case number = "Number"
        case startDate = "Start Date"
        case endDate = "End Date"
        case nickname = "Nickname"
        case politicalParty = "Political Party"
        case imageURL = "URL"
        
    }
    
    // Construct a president object
    init (name: String, number: Int, startDate: String, endDate: String, nickname: String, politicalParty: String, imageURL: String) {
        
        self.name = name
        self.number = number
        self.startDate = startDate
        self.endDate = endDate
        self.nickname = nickname
        self.politicalParty = politicalParty
        self.imageURL = imageURL
        
    }
    
}

