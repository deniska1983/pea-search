# This file is auto-generated from the current state of the database. Instead of editing this file, 
# please use the migrations feature of Active Record to incrementally modify your database, and
# then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your database schema. If you need
# to create the application database on another system, you should be using db:schema:load, not running
# all the migrations from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20111007120917) do

  create_table "dumps", :force => true do |t|
    t.string   "file"
    t.string   "os"
    t.string   "cpu"
    t.string   "disk"
    t.string   "ver"
    t.string   "user"
    t.string   "ip"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "gigasos", :force => true do |t|
    t.string   "version"
    t.string   "desc"
    t.string   "path"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "upgrades", :force => true do |t|
    t.string   "os"
    t.string   "cpu"
    t.string   "disk"
    t.string   "ver"
    t.string   "user"
    t.string   "ip"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "votes", :force => true do |t|
    t.string   "result"
    t.string   "other"
    t.string   "email"
    t.string   "ip"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

end
