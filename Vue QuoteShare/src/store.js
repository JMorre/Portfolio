import Vue from 'vue'
import Vuex from 'vuex'
import axios from 'axios';

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    user: null,
    quotes: [],
  },
  mutations: {
    setUser(state, user) {
      state.user = user;
    },
    setQuotes(state, photos) {
      state.photos = photos;
    },
  },
  actions: {
    async register(context, data) {
      try {
        let response = await axios.post("/api/users", data);
        context.commit('setUser', response.data);
        return "";
      } catch (error) {
        return error.response.data.message;
      }
    },
    async login(context, data) {
      try {
        let response = await axios.post("/api/users/login", data);
        context.commit('setUser', response.data);
        return "";
      } catch (error) {
        return error.response.data.message;
      }
    },
    async logout(context) {
      try {
        await axios.delete("/api/users");
        context.commit('setUser', null);
        return "";
      } catch (error) {
        return error.response.data.message;
      }
    },
    async getUser(context) {
      try {
        let response = await axios.get("/api/users");
        context.commit('setUser', response.data);
        return "";
      } catch (error) {
        return "";
      }
    },
    async upload(context, data) {
      try {
        await axios.post('/api/quotes', data);
        return "";
      } catch (error) {
        return error.response.data.message;
      }
    },
    async getMyQuotes(context) {
      try {
        let response = await axios.get("/api/quotes");
        context.commit('setQuotes', response.data);
        return "";
      } catch (error) {
        return "";
      }
    },
    async getAllQuotes(context) {
      try {
        let response = await axios.get("/api/quotes/all");
        context.commit('setQuotes', response.data);
        return "";
      } catch (error) {
        return "";
      }
    },
  },
})
