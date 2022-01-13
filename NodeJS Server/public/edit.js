var app = new Vue({
  el: '#edit',
  data: {
    title: "",
    description: "",
    file: null,
    createItem: null,
    uItem: null,
    items: [],
    findTitle: "",
    findItem: null,
    upError: false,
    uupError: false,
  },
  created() {
    this.getItems();
  },
  methods: {
    fileChanged(event) {
      this.file = event.target.files[0]
    },
    async upload() {
      try {
        const formData = new FormData();
        formData.append('poster', this.file, this.file.name);
        let r1 = await axios.post('/api/posters', formData);
        let r2 = await axios.post('/api/items', {
          title: this.title,
          path: r1.data.path,
          description: this.description,
        });
        this.createItem = r2.data;
        this.upError = false;
      } catch (error) {
        this.upError = true;
        console.log(error);
      }
    },
    async uupload() {
      try {
        const formData = new FormData();
        formData.append('poster', this.file, this.file.name);
        let r1 = await axios.post('/api/posters', formData);
        let r2 = await axios.post('/api/items', {
          title: this.title,
          path: r1.data.path,
          description: this.description,
        });
        this.uItem = r2.data;
        this.uupError = false;
      } catch (error) {
        this.uupError = true;
        console.log(error);
      }
    },
    async getItems() {
      try {
        let response = await axios.get("/api/items");
        this.items = response.data;
        return true;
      } catch (error) {
        console.log(error);
      }
    },
    selectItem(item) {
      this.findTitle = "";
      this.findItem = item;
    },
    async deleteItem(item) {
      try {
        let response = axios.delete("/api/items/" + item._id);
        this.findItem = null;
        this.getItems();
        this.items = response.data;
        return true;
      } catch (error) {
        console.log(error);
      }
    },
    async updateItem(item) {
      try {
        if (this.uItem === null) {
          let response = await axios.put("/api/items/" + item._id, {
            title: this.findItem.title,
            description: this.findItem.description,
            path: "",
          });
          this.findItem = null;
          this.getItems();
          this.uItem = null;
          return true;
        } else {
          let response = await axios.put("/api/items/" + item._id, {
            title: this.findItem.title,
            description: this.findItem.description,
            path: this.uItem.path,
          });
          this.findItem = null;
          this.getItems();
          this.uItem = null;
          return true;
        }
      } catch (error) {
        console.log(error);
      }
    },
  },
  computed: {
    list() {
      return this.items;
    },
  },
});
